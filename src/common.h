#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <string>

namespace VcdCT {
/* 
	Function used for displaying debugging info.
	"static const" qualifier and "inline" should provoke the compiler to optimize calls
*/
	#define foreach BOOST_FOREACH
	#define ERR(x)	ParseException::makeErrMsg(__FILE__,__LINE__,x)
	#define ERR2(x,y)	ParseException::makeErrMsg(__FILE__,__LINE__,x,y)
	
	#define DBG_MSG_ENABLED 1
	#if DBG_MSG_ENABLED == 1
	inline void DBG_MSG(const std::string &message) {
	    std::cout << message << std::endl;
	}
	
	inline void DBG_MSG(const int &message) {
	    std::cout << message << std::endl;
	}
	#else
	#define DBG_MSG(x)
	#endif
	
} //namespace

#endif //_COMMON_H_

