#ifndef PTE_LOG_H
#define PTE_LOG_H

#include <log/abstract_log.h>
#include <QPlainTextEdit>

namespace nut{

	//! shows log on the standar output stream
	class PTELog: public AbstractLog{
	public:
		PTELog(QPlainTextEdit* ptr = nullptr):_plain_text_edit_ptr(ptr){}
	    virtual ~PTELog(){}
		//! clear the plain text edit
	    virtual void Clear();
		//! display some text on the logger
	    virtual void Display(const std::string& d);

		//! set the plain text edit pointer
		void set_plain_text_edit_ptr(QPlainTextEdit* ptr){_plain_text_edit_ptr = ptr;}

	private:
		QPlainTextEdit* _plain_text_edit_ptr;
	};
	
}

//Implementation
#include "pte_log-inl.h"

#endif // COUT_LOG_H
