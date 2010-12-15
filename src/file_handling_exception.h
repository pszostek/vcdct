#ifndef _FILE_HANDLING_EXCEPTION_H_
#define _FILE_HANDLING_EXCEPTION_H_

#include <stdexcept>
#include <string>
#include <string>
#include "common.h"
#include "parse_exception.h"

namespace VcdCT {
	/**
		This class is used in main(). If any problem occurs while handling files,
		then an instance of this class is thrown.
	*/
	class FileHandlingException : public std::runtime_error {
	public:
		FileHandlingException(const std::string& msg = "Error while handling input/output file") : runtime_error(msg) {}
		static std::string makeErrMsg(const char* file, const int line) {
			return (leftBracket_ + std::string(file) + colon_ + toString(line) + rightBracket_);
		}
	};
}
#endif
