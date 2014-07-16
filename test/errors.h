/***********************************************/
#include "errors/assert_by_exception.h"
#include "errors/invariants.h"
/***********************************************/


/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "check and throw exception if needed", "[errors]" ) {
	bool exceptionThrown(false);

	SECTION("a valid logical invariant don't throw an exception"){
		try{
			nut::checkAndThrow<std::logic_error>(0 == 0,"ok");
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == false);
	}

	SECTION("a logical error must throw an exception"){
		try{
			nut::checkAndThrow<std::logic_error>(0 == 1,"nope");
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("a valid logical invariant don't throw an exception (checkAndThrowLogic)"){
		try{
			nut::checkAndThrowLogic(0 == 0,"ok");
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == false);
	}

	SECTION("a logical error must throw an exception (checkAndThrowLogic)"){
		try{
			nut::checkAndThrowLogic(0 == 1,"nope");
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("a valid logical invariant don't throw an exception (checkAndThrowRuntime)"){
		try{
			nut::checkAndThrowRuntime(0 == 0,"ok");
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == false);
	}

	SECTION("a logical error must throw an exception (checkAndThrowRuntime)"){
		try{
			nut::checkAndThrowRuntime(0 == 1,"nope");
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("checkAndThrowLogic must launch the right exception type"){
		try{
			nut::checkAndThrowLogic(0 == 1,"logic nope");
		}
		catch(std::logic_error& ex){exceptionThrown = true; std::cout << ex.what() << std::endl;}
		catch(...){}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("checkAndThrowRuntime must launch the right exception type"){
		try{
			nut::checkAndThrowRuntime(0 == 1,"runtime nope");
		}
		catch(std::runtime_error& ex){exceptionThrown = true; std::cout << ex.what() << std::endl;}
		catch(...){}
		REQUIRE(exceptionThrown == true);
	}

}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "check and throw exception if needed (with file and line)", "[errors]" ) {
	bool exceptionThrown(false);

	SECTION("a valid logical invariant don't throw an exception"){
		try{
			nut::checkAndThrow<std::logic_error>(0 == 0,"ok",__FILE__,__LINE__);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == false);
	}

	SECTION("a logical error must throw an exception"){
		try{
			nut::checkAndThrow<std::logic_error>(0 == 1,"nope",__FILE__,__LINE__);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("a valid logical invariant don't throw an exception (checkAndThrowLogic)"){
		try{
			nut::checkAndThrowLogic(0 == 0,"ok",__FILE__,__LINE__);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == false);
	}

	SECTION("a logical error must throw an exception (checkAndThrowLogic)"){
		try{
			nut::checkAndThrowLogic(0 == 1,"nope",__FILE__,__LINE__);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("a valid logical invariant don't throw an exception (checkAndThrowRuntime)"){
		try{
			nut::checkAndThrowRuntime(0 == 0,"ok",__FILE__,__LINE__);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == false);
	}

	SECTION("a logical error must throw an exception (checkAndThrowRuntime)"){
		try{
			nut::checkAndThrowRuntime(0 == 1,"nope",__FILE__,__LINE__);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("checkAndThrowLogic must launch the right exception type"){
		try{
			nut::checkAndThrowLogic(0 == 1,"logic nope",__FILE__,__LINE__);
		}
		catch(std::logic_error& ex){exceptionThrown = true; std::cout << ex.what() << std::endl;}
		catch(...){}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("checkAndThrowRuntime must launch the right exception type"){
		try{
			nut::checkAndThrowRuntime(0 == 1,"runtime nope",__FILE__,__LINE__);
		}
		catch(std::runtime_error& ex){exceptionThrown = true; std::cout << ex.what() << std::endl;}
		catch(...){}
		REQUIRE(exceptionThrown == true);
	}

}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "Preconditions", "[errors]" ) {
	bool exceptionThrown(false);

	SECTION("a valid precondition don't throw an exception"){
		try{
			PRECONDITION(0==0);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == false);
	}

	SECTION("a violated precondition must throw an exception"){
		try{
			PRECONDITION(0==1);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("a violated precondition must launch a logic exception type"){
		try{
			PRECONDITION(0==1);
		}
		catch(std::logic_error& ex){exceptionThrown = true; std::cout << ex.what() << std::endl;}
		catch(...){}
		REQUIRE(exceptionThrown == true);
	}
}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "Postconditions", "[errors]" ) {
	bool exceptionThrown(false);

	SECTION("a valid postcondition don't throw an exception"){
		try{
			POSTCONDITION(0==0);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == false);
	}

	SECTION("a violated postcondition must throw an exception"){
		try{
			POSTCONDITION(0==1);
		}catch(...){exceptionThrown = true;}
		REQUIRE(exceptionThrown == true);
	}

	SECTION("a violated postcondition must launch a logic exception type"){
		try{
			POSTCONDITION(0==1);
		}
		catch(std::logic_error& ex){exceptionThrown = true; std::cout << ex.what() << std::endl;}
		catch(...){}
		REQUIRE(exceptionThrown == true);
	}
}