/***********************************************/
#include "errors/assert_by_exception.h"
#include "errors/invariants.h"
/***********************************************/


/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "check and throw exception if needed", "[errors]" ) {

	SECTION("a valid logical invariant don't throw an exception"){
		REQUIRE_NOTHROW(nut::checkAndThrow<std::logic_error>(0 == 0,"ok"));
	}

	SECTION("a logical error must throw an exception"){
		REQUIRE_THROWS(nut::checkAndThrow<std::logic_error>(0 == 1,"nope"));
	}

	SECTION("a valid logical invariant don't throw an exception (checkAndThrowLogic)"){
		REQUIRE_NOTHROW(nut::checkAndThrowLogic(0 == 0,"ok"));
	}

	SECTION("a logical error must throw an exception (checkAndThrowLogic)"){
		REQUIRE_THROWS(nut::checkAndThrowLogic(0 == 1,"nope"));
	}

	SECTION("a valid logical invariant don't throw an exception (checkAndThrowRuntime)"){
		REQUIRE_NOTHROW(nut::checkAndThrowRuntime(0 == 0,"ok"));
	}

	SECTION("a logical error must throw an exception (checkAndThrowRuntime)"){
		REQUIRE_THROWS(nut::checkAndThrowRuntime(0 == 1,"nope"));
	}

	SECTION("checkAndThrowLogic must launch the right exception type"){
		REQUIRE_THROWS_AS(nut::checkAndThrowLogic(0 == 1,"logic nope"),std::logic_error);
	}

	SECTION("checkAndThrowRuntime must launch the right exception type"){
		REQUIRE_THROWS_AS(nut::checkAndThrowRuntime(0 == 1,"logic nope"),std::runtime_error);
	}

}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "check and throw exception if needed (with file and line)", "[errors]" ) {

	SECTION("a valid logical invariant don't throw an exception"){
		REQUIRE_NOTHROW(nut::checkAndThrow<std::logic_error>(0 == 0,"ok",__FILE__,__LINE__));
	}

	SECTION("a logical error must throw an exception"){
		REQUIRE_THROWS(nut::checkAndThrow<std::logic_error>(0 == 1,"nope",__FILE__,__LINE__));
	}

	SECTION("a valid logical invariant don't throw an exception (checkAndThrowLogic)"){
		REQUIRE_NOTHROW(nut::checkAndThrowLogic(0 == 0,"ok",__FILE__,__LINE__));
	}

	SECTION("a logical error must throw an exception (checkAndThrowLogic)"){
		REQUIRE_THROWS(nut::checkAndThrowLogic(0 == 1,"nope",__FILE__,__LINE__));
	}

	SECTION("a valid logical invariant don't throw an exception (checkAndThrowRuntime)"){
		REQUIRE_NOTHROW(nut::checkAndThrowRuntime(0 == 0,"ok",__FILE__,__LINE__));
	}

	SECTION("a logical error must throw an exception (checkAndThrowRuntime)"){
		REQUIRE_THROWS(nut::checkAndThrowRuntime(0 == 1,"nope",__FILE__,__LINE__));
	}

	SECTION("checkAndThrowLogic must launch the right exception type"){
		REQUIRE_THROWS_AS(nut::checkAndThrowLogic(0 == 1,"logic nope",__FILE__,__LINE__),std::logic_error);
	}

	SECTION("checkAndThrowRuntime must launch the right exception type"){
		REQUIRE_THROWS_AS(nut::checkAndThrowRuntime(0 == 1,"logic nope",__FILE__,__LINE__),std::runtime_error);
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