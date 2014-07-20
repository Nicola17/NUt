#ifndef TIMERS_H
#define TIMERS_H

#include <chrono>
#include <ctime>
#include "helpers/initialization_helper.h"
#include "timings/utils.h"

namespace nut{

	class Timer{
	private:
		typedef std::chrono::time_point<std::chrono::system_clock> time_point_type;

	public:
		//! return the elapsed time
		template <class UnitOfMeas>
		double elapsedTime()const;
		//! start the timer
		void start();
		//! stop the timer
		void stop();
		//! return the timer condition
		bool isStarted()const;
		//! return the availability of the elapsed time
		bool isElapsedTimeAvailable()const;

	private:
		time_point_type _start;
		time_point_type _stop;

		InitializationHelper _startedIHelper;
		InitializationHelper _timeAvailableIHelper;
	};

	
}

//Implementation
#include "timers.inl"

#endif // TIMERS_H
