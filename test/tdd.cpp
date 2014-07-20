#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

//////////////////////////////////////////
#include "log.h"
#include "errors.h"
#include "helpers.h"
#include "timings.h"
//////////////////////////////////////////


/***********************************************/
#include "timings/timers.h"
#include "timings/scoped_timers.h"
/***********************************************/

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "Timer works properly", "[timings]" ) {
	nut::Timer timer;
	int simulatedWorkTime = 50;
	
	SECTION("A newly constructed Timer is in the right condition"){
		REQUIRE( !timer.isStarted() );
		REQUIRE( !timer.isElapsedTimeAvailable() );
		REQUIRE_THROWS_AS(timer.elapsedTime<nut::Milliseconds>(),std::logic_error);
		REQUIRE_THROWS_AS(timer.stop(),std::logic_error);
	}

	SECTION("A timer execution is handled in the right way"){
		REQUIRE_NOTHROW( timer.start() );
		REQUIRE( timer.isStarted() );
		nut::sleepFor<nut::Milliseconds>(simulatedWorkTime * 1.25);
		REQUIRE_NOTHROW(timer.stop());
		REQUIRE( !timer.isStarted() );
		REQUIRE_NOTHROW( timer.elapsedTime<nut::Milliseconds>() );
		REQUIRE( timer.elapsedTime<nut::Milliseconds>() > simulatedWorkTime );
		REQUIRE( timer.elapsedTime<nut::Seconds>() > simulatedWorkTime/1000. );
		REQUIRE( timer.elapsedTime<nut::Minutes>() > simulatedWorkTime/1000./60. );
		REQUIRE( timer.elapsedTime<nut::Hours>() > simulatedWorkTime/1000./60./60. );
	}

	SECTION("Multiple starts will throw an exception"){
		REQUIRE_NOTHROW( timer.start() );
		REQUIRE_THROWS_AS( timer.start(),std::logic_error );
	}

	SECTION("Multiple stops will throw an exception"){
		REQUIRE_NOTHROW( timer.start() );
		REQUIRE_NOTHROW( timer.stop() );
		REQUIRE_THROWS_AS( timer.stop(),std::logic_error );
	}
}


TEST_CASE( "ScopedTimer works properly", "[timings]" ) {
	int simulatedWorkTime(50);

	SECTION("A scoped timer returns the elapsed time in milliseconds"){
		double time(0.);
		{
			nut::ScopedTimer<double> timer(time);
			nut::sleepFor<nut::Milliseconds>(simulatedWorkTime * 1.25);
		}
		REQUIRE( time > simulatedWorkTime );
	}

	SECTION("A scoped timer returns the elapsed time in seconds"){
		double time(0.);
		{
			nut::ScopedTimer<double,nut::Seconds> timer(time);
			nut::sleepFor<nut::Milliseconds>(simulatedWorkTime * 1.25);
		}
		REQUIRE( time > simulatedWorkTime/1000. );
	}

	SECTION("A scoped timer returns the elapsed time in seconds"){
		double time(0.);
		{
			nut::ScopedTimer<double,nut::Minutes> timer(time);
			nut::sleepFor<nut::Milliseconds>(simulatedWorkTime * 1.25);
		}
		REQUIRE( time > simulatedWorkTime/1000./60. );
	}

	SECTION("A scoped timer returns the elapsed time in seconds"){
		double time(0.);
		{
			nut::ScopedTimer<double,nut::Hours> timer(time);
			nut::sleepFor<nut::Milliseconds>(simulatedWorkTime * 1.25);
		}
		REQUIRE( time > simulatedWorkTime/1000./60./60. );
	}

}
