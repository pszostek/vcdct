#ifndef _PARSER_H_
#define _PARSER_H_

#include <fstream>
#include <iostream>
#include <stack>
#ifdef BOOST_SHARED_PTR_HPP
  #include <boost/shared_ptr.hpp>
#else
  #include "boost/shared_ptr.hpp"
#endif
#include "vcd_header.h"
#include "variable.h"
#include "vector_var.h"
#include "common.h"
#include "parse_exception.h"


namespace VcdCT {
using boost::shared_ptr;
/**
	The class is used for parsing VCD parsing purposes
	It can read its header, dumpblocks one after another
	and convert them into variables' values
*/
class VCDParser {
	public:
		shared_ptr<VCDHeader> parseHeader(const std::string& hdr) const throw(ParseException);
		std::string readInHeader(std::ifstream& inFile) const throw(ParseException);
		std::string readOneDump(std::ifstream& inFile) const throw(ParseException);
		void skipComment(std::ifstream& inFile) const throw(ParseException);
		void parseValueDump(shared_ptr<VCDHeader>& header, const std::string oneDump) const throw(ParseException);
		void writeDownFST(shared_ptr<VCDHeader>& header, std::string file);
	private:
		int parseTimescale(const std::string& in) const throw(ParseException);
		//shared_ptr<Variable> parseVariable(const std::string& in) const throw(ParseException);
		inline VectorVar::value_t expandVectorValue(const std::string& vectorValueStr, shared_ptr<VectorVar> vecPtr) const;
		inline void trimLine(std::string& in) const;
	};
}

#endif //_PARSER_H_

