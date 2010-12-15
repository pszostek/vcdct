#ifndef _PARSER_H_
#define _PARSER_H_

#include <fstream>
#include <iostream>
#include <stack>
#ifdef HAVE_BOOST_SHARED_PTR_HPP
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
		/**	The function looks for vcd-specific keywords in vcd files and maps them
			into VCDHeader object
			\param hdr File's header as std::string object
			\return Parsed file header as VCDHeader object.
		*/
		shared_ptr<VCDHeader> parseHeader(const std::string& hdr) const throw(ParseException);
		/** The function reads vcd file word by word from the beginning 
			to '$enddefinitions $end' statement and puts it into return string
			\return Read file's header
		*/
		std::string readInHeader(std::ifstream& inFile) const throw(ParseException);
		/** The function reads vcd file word by word from the current word (it should be timestep defintion)
			to the next timestep definition.
			\return single value dump (variable values for single timestep)
		*/
		std::string readOneDump(std::ifstream& inFile) const throw(ParseException);
		/** Reads file's comment and discards it. The function is used while reading file's header 
			right after readInHeader()
		*/
		void skipComment(std::ifstream& inFile) const throw(ParseException);
		/** The function takes value dump as string and parses it. All variable values are added to
			header that is given as parameter.
			\param header header object where pardes values will be stored
			\param oneDump single value dump as std::string
		*/
		void parseValueDump(shared_ptr<VCDHeader>& header, const std::string oneDump) const throw(ParseException);
	private:
		/** The function takes $timescale ... $end statement and converts it into timestep length
			\return exponent of 10 for timestep lenght expressed as 10^x
		*/
		int parseTimescale(const std::string& in) const throw(ParseException);
		/** Expands read vector value to its proper length. According to Verilog
			Reference Manual, vector value can be written in shorter form than it appears to be:
			''Vector values appear in the shortest form possible: redundant
			bit values which result from left-extending values to fill a particular vector size are eliminated.''
			For instance:	vector of length 14 with value 11111010101010	would be written as 1010101010
							vector of length 8 with value 11111111 			would be written as 1
							vector of length 8 with value 1z1z1z1z			would be written as 1z1z1z1z
			\return value expanded from short to long form
		*/
		inline VectorVar::value_t expandVectorValue(const std::string& vectorValueStr, shared_ptr<VectorVar> vecPtr) const;
		/** Removes white spaces from the end of the string */
		inline void trimLine(std::string& in) const;
	};
}

#endif //_PARSER_H_

