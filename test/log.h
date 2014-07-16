/***********************************************/
#include "log/abstract_log.h"
#include "log/cout_log.h"
#include "log/log_helper_functions.h"
/***********************************************/


/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "CoutLog works properly", "[log]" ) {
	nut::CoutLog coutLog;
	std::string testString("CoutLog test string");

	SECTION("A newly constructed CoutLog has no written char"){
		REQUIRE( coutLog.writtenChars() == 0 );
	}

	SECTION("A CoutLog print something on the std::cout"){
		coutLog.display(testString);
		REQUIRE( coutLog.writtenChars() > 0 );
	}

	SECTION("A CoutLog print a number of chars which are equal to the dimension of a string plus one"){
		coutLog.display(testString);
		REQUIRE( coutLog.writtenChars() == testString.size() + 1 );
	}

	SECTION("clear sets the number of written characters to zero"){
		coutLog.display(testString);
		coutLog.clear();
		REQUIRE( coutLog.writtenChars() == 0 );
	}
}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "CoutLog works properly in combination with the log helpers functions", "[log]" ) {
	nut::CoutLog coutLog;
	std::string testString("CoutLog + helpers test string");
	int intValue = 42;
	float floatValue = 17.17f;
	double doubleValue = 17.17;
	std::string stringValue("Talk is cheap. Show me the code!");

	SECTION("A call to secureLog on a CoutLog object print something on the std::cout"){
		secureLog(&coutLog,testString);
		REQUIRE( coutLog.writtenChars() > 0 );
	}

	SECTION("A call to secureLog on a CoutLog object with the enabled flag print something on the std::cout"){
		secureLog(&coutLog,testString,true);
		REQUIRE( coutLog.writtenChars() > 0 );
	}

	SECTION("A call to secureLog on a CoutLog object without the enabled flag don't print something on the std::cout"){
		secureLog(&coutLog,testString,false);
		REQUIRE( coutLog.writtenChars() == 0 );
	}

	SECTION("A call to secureLogValue on a CoutLog object print something on the std::cout"){
		secureLogValue(&coutLog,testString,intValue);
		REQUIRE( coutLog.writtenChars() > 0 );
	}

	SECTION("A call to secureLogValue on a CoutLog object with the enabled flag print something on the std::cout"){
		secureLogValue(&coutLog,testString,intValue,true);
		REQUIRE( coutLog.writtenChars() > 0 );
	}

	SECTION("A call to secureLogValue on a CoutLog object without the enabled flag don't print something on the std::cout"){
		secureLogValue(&coutLog,testString,intValue,false);
		REQUIRE( coutLog.writtenChars() == 0 );
	}

	SECTION("A call to secureLogValue on a CoutLog object can print an integer"){
		secureLogValue(&coutLog,testString,intValue);
		REQUIRE( coutLog.writtenChars() > 0 );
	}

	SECTION("A call to secureLogValue on a CoutLog object can print a float"){
		secureLogValue(&coutLog,testString,floatValue);
		REQUIRE( coutLog.writtenChars() > 0 );
	}

	SECTION("A call to secureLogValue on a CoutLog object can print a double"){
		secureLogValue(&coutLog,testString,doubleValue);
		REQUIRE( coutLog.writtenChars() > 0 );
	}

	SECTION("A call to secureLogValue on a CoutLog object can print a string"){
		secureLogValue(&coutLog,testString,stringValue);
		REQUIRE( coutLog.writtenChars() > 0 );
	}
}

/***********************************************/
/***********************************************/
/***********************************************/