/***********************************************/
#include "errors/assert_by_exception.h"
#include "errors/invariants.h"
/***********************************************/


/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "check and throw exception if needed", "[errors]" ) {

	SECTION("a valid logical invariant don't throw an exception"){
		REQUIRE_NOTHROW(nut::CheckAndThrow<std::logic_error>(0 == 0,"ok"));
	}

	SECTION("a logical error must throw an exception"){
		REQUIRE_THROWS(nut::CheckAndThrow<std::logic_error>(0 == 1,"nope"));
	}

	SECTION("a valid logical invariant don't throw an exception (CheckAndThrowLogic)"){
		REQUIRE_NOTHROW(nut::CheckAndThrowLogic(0 == 0,"ok"));
	}

	SECTION("a logical error must throw an exception (CheckAndThrowLogic)"){
		REQUIRE_THROWS(nut::CheckAndThrowLogic(0 == 1,"nope"));
	}

	SECTION("a valid logical invariant don't throw an exception (CheckAndThrowRuntime)"){
		REQUIRE_NOTHROW(nut::CheckAndThrowRuntime(0 == 0,"ok"));
	}

	SECTION("a logical error must throw an exception (CheckAndThrowRuntime)"){
		REQUIRE_THROWS(nut::CheckAndThrowRuntime(0 == 1,"nope"));
	}

	SECTION("CheckAndThrowLogic must launch the right exception type"){
		REQUIRE_THROWS_AS(nut::CheckAndThrowLogic(0 == 1,"logic nope"),std::logic_error);
	}

	SECTION("CheckAndThrowRuntime must launch the right exception type"){
		REQUIRE_THROWS_AS(nut::CheckAndThrowRuntime(0 == 1,"logic nope"),std::runtime_error);
	}

}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "check and throw exception if needed (with file and line)", "[errors]" ) {

	SECTION("a valid logical invariant don't throw an exception"){
		REQUIRE_NOTHROW(nut::CheckAndThrow<std::logic_error>(0 == 0,"ok",__FILE__,__LINE__));
	}

	SECTION("a logical error must throw an exception"){
		REQUIRE_THROWS(nut::CheckAndThrow<std::logic_error>(0 == 1,"nope",__FILE__,__LINE__));
	}

	SECTION("a valid logical invariant don't throw an exception (CheckAndThrowLogic)"){
		REQUIRE_NOTHROW(nut::CheckAndThrowLogic(0 == 0,"ok",__FILE__,__LINE__));
	}

	SECTION("a logical error must throw an exception (CheckAndThrowLogic)"){
		REQUIRE_THROWS(nut::CheckAndThrowLogic(0 == 1,"nope",__FILE__,__LINE__));
	}

	SECTION("a valid logical invariant don't throw an exception (CheckAndThrowRuntime)"){
		REQUIRE_NOTHROW(nut::CheckAndThrowRuntime(0 == 0,"ok",__FILE__,__LINE__));
	}

	SECTION("a logical error must throw an exception (CheckAndThrowRuntime)"){
		REQUIRE_THROWS(nut::CheckAndThrowRuntime(0 == 1,"nope",__FILE__,__LINE__));
	}

	SECTION("CheckAndThrowLogic must launch the right exception type"){
		REQUIRE_THROWS_AS(nut::CheckAndThrowLogic(0 == 1,"logic nope",__FILE__,__LINE__),std::logic_error);
	}

	SECTION("CheckAndThrowRuntime must launch the right exception type"){
		REQUIRE_THROWS_AS(nut::CheckAndThrowRuntime(0 == 1,"logic nope",__FILE__,__LINE__),std::runtime_error);
	}

}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "Preconditions", "[errors]" ) {
	SECTION("a valid precondition don't throw an exception"){
		REQUIRE_NOTHROW(PRECONDITION(0==0));
	}

	SECTION("a violated precondition must throw an exception"){
		REQUIRE_THROWS(PRECONDITION(0==1));
	}

	SECTION("a violated precondition must launch a logic exception type"){
		REQUIRE_THROWS_AS(PRECONDITION(0==1),std::logic_error);
	}
}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "Postconditions", "[errors]" ) {

	SECTION("a valid postcondition don't throw an exception"){
		REQUIRE_NOTHROW(POSTCONDITION(0==0));
	}

	SECTION("a violated postcondition must throw an exception"){
		REQUIRE_THROWS(POSTCONDITION(0==1));
	}

	SECTION("a violated postcondition must launch a logic exception type"){
		REQUIRE_THROWS_AS(POSTCONDITION(0==1),std::logic_error);
	}
}