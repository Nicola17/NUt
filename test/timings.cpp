#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"


/***********************************************/
#include "timings/timers.h"
#include "timings/scoped_timers.h"
/***********************************************/

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "Timer works properly", "[timings]" ) {
	nut::Timer timer;
	int simulated_work_time = 50;
	
	SECTION("A newly constructed Timer is in the right condition"){
		REQUIRE( !timer.IsStarted() );
		REQUIRE( !timer.IsElapsedTimeAvailable() );
		REQUIRE_THROWS_AS(timer.ElapsedTime<nut::Milliseconds>(),std::logic_error);
		REQUIRE_THROWS_AS(timer.Stop(),std::logic_error);
	}

	SECTION("A timer execution is handled in the right way"){
		REQUIRE_NOTHROW( timer.Start() );
		REQUIRE( timer.IsStarted() );
		nut::SleepFor<nut::Milliseconds>(simulated_work_time * 1.25);
		REQUIRE_NOTHROW(timer.Stop());
		REQUIRE( !timer.IsStarted() );
		REQUIRE_NOTHROW( timer.ElapsedTime<nut::Milliseconds>() );
		REQUIRE( timer.ElapsedTime<nut::Milliseconds>() > simulated_work_time );
		REQUIRE( timer.ElapsedTime<nut::Seconds>() > simulated_work_time/1000. );
		REQUIRE( timer.ElapsedTime<nut::Minutes>() > simulated_work_time/1000./60. );
		REQUIRE( timer.ElapsedTime<nut::Hours>() > simulated_work_time/1000./60./60. );
	}

	SECTION("Multiple starts will throw an exception"){
		REQUIRE_NOTHROW( timer.Start() );
		REQUIRE_THROWS_AS( timer.Start(),std::logic_error );
	}

	SECTION("Multiple stops will throw an exception"){
		REQUIRE_NOTHROW( timer.Start() );
		REQUIRE_NOTHROW( timer.Stop() );
		REQUIRE_THROWS_AS( timer.Stop(),std::logic_error );
	}
}


TEST_CASE( "ScopedTimer works properly", "[timings]" ) {
	int simulated_work_time(50);

	SECTION("A scoped timer returns the elapsed time in milliseconds"){
		double time(0.);
		{
			nut::ScopedTimer<double> timer(time);
			nut::SleepFor<nut::Milliseconds>(simulated_work_time * 1.25);
		}
		REQUIRE( time > simulated_work_time );
	}

	SECTION("A scoped timer returns the elapsed time in seconds"){
		double time(0.);
		{
			nut::ScopedTimer<double,nut::Seconds> timer(time);
			nut::SleepFor<nut::Milliseconds>(simulated_work_time * 1.25);
		}
		REQUIRE( time > simulated_work_time/1000. );
	}

	SECTION("A scoped timer returns the elapsed time in seconds"){
		double time(0.);
		{
			nut::ScopedTimer<double,nut::Minutes> timer(time);
			nut::SleepFor<nut::Milliseconds>(simulated_work_time * 1.25);
		}
		REQUIRE( time > simulated_work_time/1000./60. );
	}

	SECTION("A scoped timer returns the elapsed time in seconds"){
		double time(0.);
		{
			nut::ScopedTimer<double,nut::Hours> timer(time);
			nut::SleepFor<nut::Milliseconds>(simulated_work_time * 1.25);
		}
		REQUIRE( time > simulated_work_time/1000./60./60. );
	}

}
