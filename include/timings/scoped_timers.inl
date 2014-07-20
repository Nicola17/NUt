#ifndef SCOPED_TIMERS_INL
#define SCOPED_TIMERS_INL

#include <chrono>
#include <ctime>
#include "timings/timers.h"
#include "timings/utils.h"

namespace nut{

	template <class T, class UnitOfMeas>
	ScopedTimer<T,UnitOfMeas>::ScopedTimer(T& elapsedTime):
		_elapsedTime(elapsedTime)
	{
		_timer.start();
	}

	template <class T, class UnitOfMeas>
	ScopedTimer<T,UnitOfMeas>::~ScopedTimer(){
		_timer.stop();
		_elapsedTime = static_cast<T>(_timer.elapsedTime<UnitOfMeas>());
	}
	
}

#endif // SCOPED_TIMERS_INL
