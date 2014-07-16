#ifndef COUT_LOG_INL
#define COUT_LOG_INL

#include <iostream>

namespace nut{

	inline void CoutLog::clear(){
		_nCharWritten = 0;
	}

	inline void CoutLog::display(const std::string& d){
		std::cout << d << std::endl;
		_nCharWritten += d.size() + 1; 
	}

	inline unsigned int CoutLog::writtenChars()const{
		return _nCharWritten;
	}
	
}

#endif // COUT_LOG_INL
