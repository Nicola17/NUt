#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

/***********************************************/
#include "progress/cout_progress.h"
#include "progress/progress_reduction.h"
/***********************************************/

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "CoutProgress works properly", "[timings]" ) {
	nut::CoutProgress progress;

	REQUIRE(progress.GetMinimum() == 0);
	REQUIRE(progress.GetMaximum() == 100);
	REQUIRE(progress.GetCurrentPosition() == 0);
	REQUIRE(!progress.IsCanceled());
	REQUIRE(progress.GetMinimum() <= progress.GetCurrentPosition());
	REQUIRE(progress.GetMaximum() >= progress.GetCurrentPosition());

	SECTION("Getter/Setter works properly"){
		int minimum = 50;
		int maximum = 500;
		int current = 150;
		REQUIRE_NOTHROW(progress.SetMinimum(minimum));
		REQUIRE_NOTHROW(progress.SetMaximum(maximum));
		REQUIRE_NOTHROW(progress.SetCurrentPosition(current));
		REQUIRE(minimum == progress.GetMinimum());
		REQUIRE(maximum == progress.GetMaximum());
		REQUIRE(current == progress.GetCurrentPosition());
	}

	SECTION("Make a step works properly in a standard situation"){
		auto position = progress.GetCurrentPosition();
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE(progress.GetCurrentPosition() == position+1);
	}

	SECTION("Make a step works properly in a limit situation"){
		int minimum = 0;
		int maximum = 100;
		int current = 100;
		REQUIRE_NOTHROW(progress.SetMinimum(minimum));
		REQUIRE_NOTHROW(progress.SetMaximum(maximum));
		REQUIRE_NOTHROW(progress.SetCurrentPosition(current));
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE(progress.GetMaximum() == progress.GetCurrentPosition());
	}
	SECTION("If you set an invalid position a logic error is thrown"){
		int minimum = 0;
		int maximum = 100;
		int current = 150;
		REQUIRE_NOTHROW(progress.SetMinimum(minimum));
		REQUIRE_NOTHROW(progress.SetMaximum(maximum));
		REQUIRE_THROWS_AS(progress.SetCurrentPosition(current),std::logic_error);
		REQUIRE(progress.GetMinimum() <= progress.GetCurrentPosition());
		REQUIRE(progress.GetMaximum() >= progress.GetCurrentPosition());
	}

	SECTION("A reset restore the current position to the minimum"){
		int minimum = 0;
		int maximum = 100;
		int current = 50;
		REQUIRE_NOTHROW(progress.SetMinimum(minimum));
		REQUIRE_NOTHROW(progress.SetMaximum(maximum));
		REQUIRE_NOTHROW(progress.SetCurrentPosition(current));
		REQUIRE(progress.GetCurrentPosition() != progress.GetMinimum());
		REQUIRE_NOTHROW(progress.Reset());
		REQUIRE(progress.GetCurrentPosition() == progress.GetMinimum());
	}

	SECTION("A change in the minimum don't invalidate the current position"){
		int minimum = 0;
		int maximum = 100;
		int current = 50;
		int new_min = 70;

		REQUIRE_NOTHROW(progress.SetMinimum(minimum));
		REQUIRE_NOTHROW(progress.SetMaximum(maximum));
		REQUIRE_NOTHROW(progress.SetCurrentPosition(current));
		REQUIRE_NOTHROW(progress.SetMinimum(new_min));

		REQUIRE(progress.GetMinimum() <= progress.GetCurrentPosition());
		REQUIRE(progress.GetMaximum() >= progress.GetCurrentPosition());
	}
	
	SECTION("A change in the maximum don't invalidate the current position"){
		int minimum = 0;
		int maximum = 100;
		int current = 50;
		int new_max = 30;

		REQUIRE_NOTHROW(progress.SetMinimum(minimum));
		REQUIRE_NOTHROW(progress.SetMaximum(maximum));
		REQUIRE_NOTHROW(progress.SetCurrentPosition(current));
		REQUIRE_NOTHROW(progress.SetMaximum(new_max));

		REQUIRE(progress.GetMinimum() <= progress.GetCurrentPosition());
		REQUIRE(progress.GetMaximum() >= progress.GetCurrentPosition());
	}
	SECTION("A change in the maximum don't invalidate the current position"){
		int minimum = 0;
		int maximum = 10;
		int current = 0;
		int new_max = 30;

		REQUIRE_NOTHROW(progress.SetMinimum(minimum));
		REQUIRE_NOTHROW(progress.SetMaximum(maximum));
		REQUIRE_NOTHROW(progress.SetCurrentPosition(current));
		REQUIRE_THROWS_AS(progress.progress_bar_tokens(-1),std::logic_error);
		REQUIRE_NOTHROW(progress.progress_bar_tokens(40));
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE_NOTHROW(progress.MakeAStep());
		REQUIRE_NOTHROW(progress.MakeAStep());
	}
	
}

/***********************************************/
/***********************************************/
/***********************************************/

TEST_CASE( "ProgressReduction works properly", "[timings]" ) {
	nut::CoutProgress progress;
	progress.SetMinimum(0);
	progress.SetMaximum(10);
	progress.SetCurrentPosition(0);
		
	SECTION("ratio < 1"){
		nut::ProgressReduction prgRed;
		REQUIRE(prgRed.external_progress() == 0);
		REQUIRE(prgRed.num_external_steps() == 0);
		REQUIRE(prgRed.num_internal_steps() == 0);
		REQUIRE(prgRed.reduction_ratio() == 0);
		REQUIRE(prgRed.IsCanceled() == false);
		
		REQUIRE_NOTHROW(prgRed.set_external_progress(&progress));
		REQUIRE(prgRed.external_progress() == &progress);
		REQUIRE_NOTHROW(prgRed.set_num_external_steps(10));
		REQUIRE(prgRed.num_external_steps() == 10);
		REQUIRE_NOTHROW(prgRed.set_num_internal_steps(20));
		REQUIRE(prgRed.num_internal_steps() == 20);
		REQUIRE(prgRed.reduction_ratio() == 0.5);
		
		prgRed.MakeAStep();
		prgRed.MakeAStep();
		prgRed.MakeAStep();

		REQUIRE(progress.GetCurrentPosition() == 1);

		prgRed.Finalize();
		REQUIRE(progress.GetCurrentPosition() == progress.GetMaximum());
		prgRed.MakeAStep();
		REQUIRE(progress.GetCurrentPosition() == progress.GetMaximum());
	}

	SECTION("ratio > 1"){
		nut::ProgressReduction prgRed;
		REQUIRE(prgRed.external_progress() == 0);
		REQUIRE(prgRed.num_external_steps() == 0);
		REQUIRE(prgRed.num_internal_steps() == 0);
		REQUIRE(prgRed.reduction_ratio() == 0);
		REQUIRE(prgRed.IsCanceled() == false);
		
		REQUIRE_NOTHROW(prgRed.set_external_progress(&progress));
		REQUIRE(prgRed.external_progress() == &progress);
		REQUIRE_NOTHROW(prgRed.set_num_external_steps(10));
		REQUIRE(prgRed.num_external_steps() == 10);
		REQUIRE_NOTHROW(prgRed.set_num_internal_steps(3));
		REQUIRE(prgRed.num_internal_steps() == 3);
		REQUIRE(prgRed.reduction_ratio() == 10./3);
		
		prgRed.MakeAStep();
		REQUIRE(progress.GetCurrentPosition() == 3);

		prgRed.MakeAStep();
		prgRed.MakeAStep();
		REQUIRE(progress.GetCurrentPosition() == progress.GetMaximum());
		prgRed.MakeAStep();
		REQUIRE(progress.GetCurrentPosition() == progress.GetMaximum());
	}

	SECTION("multiple progress reductions"){
		nut::ProgressReduction prgRed0;
		nut::ProgressReduction prgRed1;
		
		REQUIRE_NOTHROW(prgRed0.set_external_progress(&progress));
		REQUIRE_NOTHROW(prgRed1.set_external_progress(&progress));

		REQUIRE_NOTHROW(prgRed0.set_num_external_steps(2));
		REQUIRE_NOTHROW(prgRed1.set_num_external_steps(8));

		REQUIRE_NOTHROW(prgRed0.set_num_internal_steps(300));
		REQUIRE_NOTHROW(prgRed1.set_num_internal_steps(2));
		
		prgRed0.MakeAStep();
		REQUIRE(progress.GetCurrentPosition() == 0);
		prgRed0.Finalize();
		REQUIRE(progress.GetCurrentPosition() == 2);

		prgRed1.MakeAStep();
		REQUIRE(progress.GetCurrentPosition() == 6);

		prgRed1.Finalize();
		REQUIRE(progress.GetCurrentPosition() == progress.GetMaximum());
		prgRed1.MakeAStep();
		REQUIRE(progress.GetCurrentPosition() == progress.GetMaximum());
		prgRed0.MakeAStep();
		REQUIRE(progress.GetCurrentPosition() == progress.GetMaximum());
	}
}
