#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <string>
#include <sstream>
#ifdef HAVE_BOOST_FOREACH_HPP
	#include <boost/foreach.hpp>
#else
	#include "boost/foreach.hpp"
#endif
namespace VcdCT {
	#define foreach BOOST_FOREACH
	#define ERR(x)	ParseException::makeErrMsg(__FILE__,__LINE__,x)
	#define ERR2(x,y)	ParseException::makeErrMsg(__FILE__,__LINE__,x,y)
	
	#define DBG_MSG_ENABLED 1
	#if DBG_MSG_ENABLED == 1
/** 
	Function used for displaying debugging info.
	"static const" qualifier and "inline" should provoke the compiler to optimize calls
*/
	inline void DBG_MSG(const std::string &message) {
	    std::cout << message << std::endl;
	}
	
	inline void DBG_MSG(const int &message) {
	    std::cout << message << std::endl;
	}
	#else
	#define DBG_MSG(x)
	#endif
	/**
		Function written to replace boost::lexical_cast
		Allows conversion from std::string to desired type
	*/
	template<typename T> T fromString(const std::string str) {
		std::istringstream stream;
		T ret;
		stream.str(str);
		stream >> ret;
		return ret;
	}
	/**
		Function written to replace boost::lexical_cast
		Allows conversion from any format to std::string 
	*/
	template<typename T> std::string toString(const T sth) {
		std::ostringstream stream;
		stream << sth;
		return stream.str();
	}
} //namespace

#endif //_COMMON_H_

