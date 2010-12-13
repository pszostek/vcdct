#ifndef _PARSEEXCEPTION_H_
#define _PARSEEXCEPTION_H_

#include <stdexcept>
#include <string>
#include <boost/lexical_cast.hpp>

using boost::lexical_cast;

namespace VcdCT {
	const static std::string colon_ = std::string(":");
	const static std::string leftBracket_ = std::string("[");
	const static std::string rightBracket_ = std::string("]");
	const static std::string space_ = std::string(" ");

	class ParseException : public std::runtime_error {
	public:
		ParseException(const std::string& msg = "Error while parsing input file") : runtime_error(msg) {}
		static std::string makeErrMsg(const char* file, const int line) {
			return (leftBracket_ + std::string(file) + colon_ + lexical_cast<std::string>(line) + rightBracket_);
		}
		static std::string makeErrMsg(const char* file, const int line, const std::string& msg) {
			return (leftBracket_ + std::string(file) + colon_ + lexical_cast<std::string>(line) + rightBracket_ + space_ + msg);
		}
		static std::string makeErrMsg(const char* file, const int line, const std::string& msg1,const std::string& msg2) {
			return (leftBracket_ + std::string(file) + colon_ + lexical_cast<std::string>(line) + rightBracket_ + space_ + msg1 + space_ + msg2);
		}
	};
} //namespace
#endif

