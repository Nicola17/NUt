#ifndef INITIALIZATION_HELPER_H
#define INITIALIZATION_HELPER_H

namespace nut{

	class InitializationHelper{
	public:
		//! Create an unitialized object
		InitializationHelper();
		//! Initialize the helper
		void initialize();
		//! Deinitialize the helper
		void deinitialize();
		//! Throw a logic error if the helper is not initialized
		void checkInitialized()const;
		//! Throw a logic error if the helper is initialized
		void checkUninitialized()const;
		//! Return the helper state
		bool isInitialized()const;

	private:
		bool _initialized;
	};

	
}

//Implementation
#include "initialization_helper.inl"

#endif // INITIALIZATION_HELPER_H
