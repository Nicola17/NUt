#ifndef TIMERS_INL
#define TIMERS_INL

namespace nut{

	template <class UnitOfMeas>
	double Timer::elapsedTime()const{
		_timeAvailableIHelper.checkInitialized();
		return std::chrono::duration<double,typename UnitOfMeas::period>(_stop-_start).count();
	}
	void Timer::start(){
		_startedIHelper.checkUninitialized();
		_startedIHelper.initialize();
		if(_timeAvailableIHelper.isInitialized())
			_timeAvailableIHelper.deinitialize();
		_start = std::chrono::system_clock::now();
	}
	void Timer::stop(){
		_startedIHelper.checkInitialized();
		_startedIHelper.deinitialize();
		_timeAvailableIHelper.initialize();
		_stop = std::chrono::system_clock::now();
	}
	bool Timer::isStarted()const{
		return _startedIHelper.isInitialized();
	}
	bool Timer::isElapsedTimeAvailable()const{
		return _timeAvailableIHelper.isInitialized();
	}
	
}

#endif // TIMERS_INL