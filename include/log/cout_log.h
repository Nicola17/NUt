#ifndef COUT_LOG_H
#define COUT_LOG_H

#include <string>
#include <sstream>

namespace nut{

	//! shows log on the standar output stream
	class CoutLog: public AbstractLog{
	public:
		CoutLog():_nCharWritten(0){}
	    virtual ~CoutLog(){}
		//! set the number of written characters to zero
	    virtual void clear();
		//! display some text on the logger
	    virtual void display(const std::string& d);
	    //! return the number of written character
	    unsigned int writtenChars()const;
	    	
	private:
		unsigned int _nCharWritten;
	};
	
}

//Implementation
#include "cout_log.inl"

#endif // COUT_LOG_H
