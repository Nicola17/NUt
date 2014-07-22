#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

/***********************************************/
#include "helpers/initialization_helper.h"
#include "helpers/object_counter.h"
/***********************************************/

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "Initialization helper works properly", "[helpers]" ) {
	nut::InitializationHelper init_helper;
	
	SECTION("A newly constructed InitializationHelper is not initialized"){
		REQUIRE( !init_helper.IsInitialized() );
	}
	SECTION("A call to initialize initializes the helper"){
		init_helper.Initialize();
		REQUIRE( init_helper.IsInitialized() );
	}
	SECTION("A call to deinitialize deinitializes the helper"){
		init_helper.Initialize();
		init_helper.Uninitialize();
		REQUIRE( !init_helper.IsInitialized() );
	}
	SECTION("A call to checkInitialized on an uninitialized object must throws a logic error"){
		REQUIRE_THROWS_AS( init_helper.CheckInitialized(), std::logic_error );
		REQUIRE_NOTHROW( init_helper.CheckUninitialized() );
	}
	SECTION("A call to checkUninitialized on an initialized object must throws a logic error"){
		init_helper.Initialize();
		REQUIRE_THROWS_AS( init_helper.CheckUninitialized(), std::logic_error );
		REQUIRE_NOTHROW( init_helper.CheckInitialized() );
	}
	SECTION("Only an uninitialized object can be initialized"){
		REQUIRE_THROWS_AS( init_helper.Uninitialize(), std::logic_error );
	}
	SECTION("Only an initialized object can be deinitialized"){
		init_helper.Initialize();
		REQUIRE_THROWS_AS( init_helper.Initialize(), std::logic_error );
	}
}

TEST_CASE( "ObjectCounter helper works properly", "[helpers]" ) {
	class CountableClass: nut::ObjectCounter<CountableClass>{
	};
	class YetAnotherCountableClass: nut::ObjectCounter<YetAnotherCountableClass>{
	};

	{
		CountableClass countable_object;
		REQUIRE(nut::ObjectCounter<CountableClass>::objects_created() == 1);
		REQUIRE(nut::ObjectCounter<CountableClass>::objects_alive() == 1);
	}

	REQUIRE(nut::ObjectCounter<CountableClass>::objects_created() == 1);
	REQUIRE(nut::ObjectCounter<CountableClass>::objects_alive() == 0);

	{
		CountableClass countable_object_0;
		CountableClass countable_object_1;
		CountableClass countable_object_2;
		REQUIRE(nut::ObjectCounter<CountableClass>::objects_created() == 4);
		REQUIRE(nut::ObjectCounter<CountableClass>::objects_alive() == 3);
	}

	REQUIRE(nut::ObjectCounter<CountableClass>::objects_created() == 4);
	REQUIRE(nut::ObjectCounter<CountableClass>::objects_alive() == 0);

	{
		YetAnotherCountableClass countable_object;
		REQUIRE(nut::ObjectCounter<YetAnotherCountableClass>::objects_created() == 1);
		REQUIRE(nut::ObjectCounter<YetAnotherCountableClass>::objects_alive() == 1);
		REQUIRE(nut::ObjectCounter<CountableClass>::objects_created() == 4);
		REQUIRE(nut::ObjectCounter<CountableClass>::objects_alive() == 0);
	}
}
