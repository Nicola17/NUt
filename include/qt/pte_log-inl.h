#ifndef PTE_LOG_INL
#define PTE_LOG_INL

#include <iostream>
#include <errors\invariants.h>

namespace nut{

	inline void PTELog::Clear(){
		PRECONDITION(_plain_text_edit_ptr != nullptr);
		_plain_text_edit_ptr->clear();
		QCoreApplication::processEvents();
	}

	inline void PTELog::Display(const std::string& d){
		PRECONDITION(_plain_text_edit_ptr != nullptr);
		_plain_text_edit_ptr->appendPlainText(QString::fromStdString(d));
		QCoreApplication::processEvents();
	}
	
}

#endif // COUT_LOG_INL
