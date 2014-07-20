#ifndef INITIALIZATION_HELPER_INL
#define INITIALIZATION_HELPER_INL

#include "errors/invariants.h"
#include "errors/assert_by_exception.h"
namespace nut{

	inline InitializationHelper::InitializationHelper():_initialized(false){

	}
	inline void InitializationHelper::initialize(){
		PRECONDITION(!isInitialized());
		_initialized = true;
		POSTCONDITION(isInitialized());
	}
	inline void InitializationHelper::deinitialize(){
		PRECONDITION(isInitialized());
		_initialized = false;
		POSTCONDITION(!isInitialized());	
	}
	inline void InitializationHelper::checkInitialized()const{
		checkAndThrowLogic(_initialized,"Initialization check failed!!");
	}
	inline void InitializationHelper::checkUninitialized()const{
		checkAndThrowLogic(!_initialized,"Uninitialization check failed!!");
	}
	inline bool InitializationHelper::isInitialized()const{
		return _initialized;		
	}
}

#endif // INITIALIZATION_HELPER_INL