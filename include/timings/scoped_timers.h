#ifndef SCOPED_TIMERS_H
#define SCOPED_TIMERS_H

#include <chrono>
#include <ctime>
#include "timings/timers.h"
#include "timings/utils.h"

namespace nut{

	template <class T, class UnitOfMeas = Milliseconds>
	class ScopedTimer{
	public:
		//! start the timer
		ScopedTimer(T& elapsedTime);
		//! stop the timer and save the elapsedTime
		~ScopedTimer();
	
	private:
		Timer 	_timer;
		T& 		_elapsedTime;
	};
	
}

//Implementation
#include "scoped_timers.inl"

#endif // SCOPED_TIMERS_H
