#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

/***********************************************/
#include "log/abstract_log.h"
#include "log/cout_log.h"
#include "log/log_helper_functions.h"
/***********************************************/


/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "CoutLog works properly", "[log]" ) {
	nut::CoutLog cout_log;
	std::string test_string("CoutLog test string");

	SECTION("A newly constructed CoutLog has no written char"){
		REQUIRE( cout_log.num_written_chars() == 0 );
	}

	SECTION("A CoutLog print something on the std::cout"){
		cout_log.Display(test_string);
		REQUIRE( cout_log.num_written_chars() > 0 );
	}

	SECTION("A CoutLog print a number of chars which are equal to the dimension of a string plus one"){
		cout_log.Display(test_string);
		REQUIRE( cout_log.num_written_chars() == test_string.size() + 1 );
	}

	SECTION("clear sets the number of written characters to zero"){
		cout_log.Display(test_string);
		cout_log.Clear();
		REQUIRE( cout_log.num_written_chars() == 0 );
	}
}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "CoutLog works properly in combination with the log helpers functions", "[log]" ) {
	nut::CoutLog cout_log;
	std::string test_string("CoutLog + helpers test string");
	int intValue = 42;
	float floatValue = 17.17f;
	double doubleValue = 17.17;
	std::string stringValue("Talk is cheap. Show me the code!");

	SECTION("A call to SecureLog on a CoutLog object print something on the std::cout"){
		SecureLog(&cout_log,test_string);
		REQUIRE( cout_log.num_written_chars() > 0 );
	}

	SECTION("A call to SecureLog on a CoutLog object with the enabled flag print something on the std::cout"){
		SecureLog(&cout_log,test_string,true);
		REQUIRE( cout_log.num_written_chars() > 0 );
	}

	SECTION("A call to SecureLog on a CoutLog object without the enabled flag don't print something on the std::cout"){
		SecureLog(&cout_log,test_string,false);
		REQUIRE( cout_log.num_written_chars() == 0 );
	}

	SECTION("A call to SecureLogValue on a CoutLog object print something on the std::cout"){
		SecureLogValue(&cout_log,test_string,intValue);
		REQUIRE( cout_log.num_written_chars() > 0 );
	}

	SECTION("A call to SecureLogValue on a CoutLog object with the enabled flag print something on the std::cout"){
		SecureLogValue(&cout_log,test_string,intValue,true);
		REQUIRE( cout_log.num_written_chars() > 0 );
	}

	SECTION("A call to SecureLogValue on a CoutLog object without the enabled flag don't print something on the std::cout"){
		SecureLogValue(&cout_log,test_string,intValue,false);
		REQUIRE( cout_log.num_written_chars() == 0 );
	}

	SECTION("A call to SecureLogValue on a CoutLog object can print an integer"){
		SecureLogValue(&cout_log,test_string,intValue);
		REQUIRE( cout_log.num_written_chars() > 0 );
	}

	SECTION("A call to SecureLogValue on a CoutLog object can print a float"){
		SecureLogValue(&cout_log,test_string,floatValue);
		REQUIRE( cout_log.num_written_chars() > 0 );
	}

	SECTION("A call to SecureLogValue on a CoutLog object can print a double"){
		SecureLogValue(&cout_log,test_string,doubleValue);
		REQUIRE( cout_log.num_written_chars() > 0 );
	}

	SECTION("A call to SecureLogValue on a CoutLog object can print a string"){
		SecureLogValue(&cout_log,test_string,stringValue);
		REQUIRE( cout_log.num_written_chars() > 0 );
	}
}

/***********************************************/
/***********************************************/
/***********************************************/