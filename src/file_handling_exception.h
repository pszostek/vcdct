#ifndef _FILE_HANDLING_EXCEPTION_H_
#define _FILE_HANDLING_EXCEPTION_H_

#include <stdexcept>
#include <string>
#include <boost/lexical_cast.hpp>
#include <string>
#include "parse_exception.h"

namespace VcdCT {
	class FileHandlingException : public std::runtime_error {
	public:
		FileHandlingException(const std::string& msg = "Error while handling input/output file") : runtime_error(msg) {}
		static std::string makeErrMsg(const char* file, const int line) {
			return (leftBracket_ + std::string(file) + colon_ + boost::lexical_cast<std::string>(line) + rightBracket_);
		}
	};
}
#endif
