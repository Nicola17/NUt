#ifndef LOG_HELPER_FUNCTIONS_H
#define LOG_HELPER_FUNCTIONS_H

#include <string>
#include <sstream>

namespace nut{
	template <class Logger>
	inline void secureLog(Logger* logPtr, const std::string& text, bool enabled = true){
		if(enabled){
			if(logPtr!=nullptr){
				logPtr->display(text);
			}
		}
	}

	template <class Logger, class Data>
	inline void secureLogValue(Logger* logPtr, const std::string& text, const Data& v, bool enabled = true){
		if(enabled){
			if(logPtr!=nullptr){
				std::stringstream ss;
				ss << text << ": " << v;
				logPtr->display(ss.str());
			}
		}
	}
}

#endif // LOG_HELPER_FUNCTIONS_H