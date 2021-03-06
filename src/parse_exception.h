#ifndef _PARSEEXCEPTION_H_
#define _PARSEEXCEPTION_H_

#include <stdexcept>
#include <string>
#include "common.h"

namespace VcdCT {
	const static std::string colon_ = std::string(":");
	const static std::string leftBracket_ = std::string("[");
	const static std::string rightBracket_ = std::string("]");
	const static std::string space_ = std::string(" ");

	/**
		This class is used by VCDParser objects
		If any problem occurs while parsin, then an instance
		of this class is thrown
	*/
	class ParseException : public std::runtime_error {
	public:
		ParseException(const std::string& msg = "Error while parsing input file") : runtime_error(msg) {}
		/** This function creates an error message, that is put later into exception object and
			displayed with what()
		*/
		static std::string makeErrMsg(const char* file, const int line) {
			return (leftBracket_ + std::string(file) + colon_ + toString(line) + rightBracket_);
		}
		/** This function creates an error message, that is put later into exception object and
			displayed with what()
		*/
		static std::string makeErrMsg(const char* file, const int line, const std::string& msg) {
			return (leftBracket_ + std::string(file) + colon_ + toString(line) + rightBracket_ + space_ + msg);
		}
		/** This function creates an error message, that is put later into exception object and
			displayed with what()
		*/
		static std::string makeErrMsg(const char* file, const int line, const std::string& msg1,const std::string& msg2) {
			return (leftBracket_ + std::string(file) + colon_ + toString(line) + rightBracket_ + space_ + msg1 + space_ + msg2);
		}
	};
} //namespace
#endif

