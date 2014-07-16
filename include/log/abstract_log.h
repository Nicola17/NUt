#ifndef ABSTRACT_LOG_H
#define ABSTRACT_LOG_H

#include <string>
#include <sstream>

namespace nut{

	//! Abstract interface for a general logger
	class AbstractLog{
	public:
	    virtual ~AbstractLog(){}
		//! clear the log
	    virtual void clear()=0;
		//! display some text on the logger
	    virtual void display(const std::string& d)=0;
	};

}
#endif // ABSTRACTLOG_H
