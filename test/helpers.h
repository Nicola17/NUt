/***********************************************/
#include "helpers/initialization_helper.h"
/***********************************************/


/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "Initialization helper works properly", "[helpers]" ) {
	nut::InitializationHelper initHelper;
	
	SECTION("A newly constructed InitializationHelper is not initialized"){
		REQUIRE( !initHelper.isInitialized() );
	}
	SECTION("A call to initialize initializes the helper"){
		initHelper.initialize();
		REQUIRE( initHelper.isInitialized() );
	}
	SECTION("A call to deinitialize deinitializes the helper"){
		initHelper.initialize();
		initHelper.deinitialize();
		REQUIRE( !initHelper.isInitialized() );
	}
	SECTION("A call to checkInitialized on an uninitialized object must throws a logic error"){
		REQUIRE_THROWS_AS( initHelper.checkInitialized(), std::logic_error );
		REQUIRE_NOTHROW( initHelper.checkUninitialized() );
	}
	SECTION("A call to checkUninitialized on an initialized object must throws a logic error"){
		initHelper.initialize();
		REQUIRE_THROWS_AS( initHelper.checkUninitialized(), std::logic_error );
		REQUIRE_NOTHROW( initHelper.checkInitialized() );
	}
	SECTION("Only an uninitialized object can be initialized"){
		REQUIRE_THROWS_AS( initHelper.deinitialize(), std::logic_error );
	}
	SECTION("Only an initialized object can be deinitialized"){
		initHelper.initialize();
		REQUIRE_THROWS_AS( initHelper.initialize(), std::logic_error );
	}
}



