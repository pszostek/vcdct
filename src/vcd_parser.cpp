#include <ctype.h>
#include <sstream>
#include <utility>
#include <vector>
#include <stack>
#include <string>
#include <algorithm>

#include "common.h"
#include "vcd_parser.h"
#include "parse_exception.h"
#include "scalar_var.h"
#include "variable.h"
#include "vector_var.h"
#include "var_type_hash.hpp"
#include "var_type_code.h"

using boost::shared_ptr;

namespace VcdCT{
	/**
		The function reads header's tokens one after another
		and interprets them as definition of: date, version, timescale,
		up- and downscopes and variables
		 
		\param hdr File's header in a form of a string
		\return Object of VCDHeader class, that contains all parsed header data
	*/
	shared_ptr<VCDHeader> VCDParser::parseHeader(const std::string& hdr) const throw(ParseException) {
        shared_ptr<VCDHeader> header(new VCDHeader);
		std::istringstream istream(hdr);
		std::string token;
		std::vector<std::pair<Variable::ScopeType, std::string> > scopes;
		
		for(;;) { /* parse file's header until all valuable informations are extracted */		
			istream >> token;
			if(token == "$date") {
				std::string date;
				for(;;) { //read in and concatenate all data until "$end" occurs
					if(!istream.good()) { //there are no words in input stream and $end was not found
						throw ParseException(ERR("Date statement is badly formed"));
					}
					istream >> token;
					if(token == "$end")
						break;
					date += token + " ";
				}
				header->setDate(date);		
				continue;
			}
			if(token == "$version") {
				std::string version;
				for(;;) { ///read in and concatenate all data until "$end" occurs
					if(!istream.good()) { ///there are no words in input stream and $end was not found
						throw ParseException(ERR("Version statement is badly formed"));
					}
					istream >> token;
					if(token == "$end")
						break;
					version += token + " ";
				}
				trimLine(version);
				header->setVersion(version);		
				continue;
			}
			if(token == "$timescale") {
				std::string timescale;
				for(;;) { ///read in and concatenate all data until "$end" occurs
					if(!istream.good()) { ///there are no words in input stream and $end was not found
						throw ParseException(ERR("Version statement is badly formed"));
					}
					istream >> token;
					if(token == "$end")
						break;
					timescale += token + " ";
				}
				trimLine(timescale);
				header->setTimescale(parseTimescale(timescale));		
				continue;
			}
			if(token == "$scope") {
				/* 
					each $scope block consist of "$scope", scope name, scope type
					and "$end" keyword.
				*/ 
				std::string name, type, end;
				istream >> type >> name >> end;
				Variable::ScopeType t;
			    if(type == "module") {
			        t = Variable::MODULE;
			    } else if(type == "task") {
			         t = Variable::TASK;
			    } else if(type == "function") {
			         t = Variable::FUNCTION;
			    } else if(type == "begin") {
			         t = Variable::BEGIN;
			    } else if(type == "fork") {
			         t = Variable::FORK;
			    } else {
			        throw ParseException(ERR("Unknow scope type"));
			    }
				scopes.push_back(std::make_pair(t, name));
				if( end != "$end")
					throw ParseException(ERR("Scope statement is badly formed"));
				continue;
			}
			if(token == "$upscope") {
				istream >> token;
				if(scopes.empty() || token != "$end")
					throw ParseException(ERR("File header badly formed - too much $scope $end tokens"));
				scopes.pop_back();
				continue;
			}
			if(token == "$var") {
				/**
					each variable definition consists of: "$var", var type,
					var length, var id, var reference and "$end"
				*/
				std::string type, length_str, id, reference;
				istream >> type >> length_str >> id;
				for(;;) {
					if(!istream.good()) { //there are no words in input stream and $end was not found
						throw ParseException(ERR("Veriable statement is badly formed"));
					}
					istream >> token;
					if(token == "$end")
						break;
					reference += token + " ";
				}
				trimLine(reference);
				const VarType* varType = Perfect_Hash::IsValidVarType(type.c_str(), type.length());
				if(varType == NULL)
					throw ParseException(ERR("Unknown variable type"));
					
				/** 
					Check variable length and determine its type.
					If length is equal to one, then it should be a scalar.
					If length is greater than one, then it shoudl be a vector
				*/ 
				short length = fromString<short>(length_str);
				if(length == 1) { //scalar variable (of length 1)
					//creat new scalar
					shared_ptr<ScalarVar> ret = shared_ptr<ScalarVar>(new ScalarVar((VarTypeCode::VarTypeEnum)varType->VarTypeCode, id, reference));
					ret->setScopes(scopes);
					std::pair<std::map<std::string,shared_ptr<ScalarVar> >::iterator, bool> addReturnValue;
		    		addReturnValue = header->addScalar(ret);
		    		
		    		//if one with the same ID was previously added, report an error
		    		if(addReturnValue.second == false && addReturnValue.first->second->getIdentifier() != ret->getIdentifier())
						throw ParseException(ERR("File header badly formed -  scalar variable identifier repeated: " + ret->getIdentifier()));
				} else { //vector variable
					//creat new vector
					shared_ptr<VectorVar> ret = shared_ptr<VectorVar> (new VectorVar((VarTypeCode::VarTypeEnum)varType->VarTypeCode, id, reference, length));
					ret->setScopes(scopes);
					std::pair<std::map<std::string,shared_ptr<VectorVar> >::iterator, bool> addReturnValue;
		    		addReturnValue = header->addVector(ret);
		    		
		    		//if one with the same ID was previously added, report an error
		    		if(addReturnValue.second == false && addReturnValue.first->second->getIdentifier() != ret->getIdentifier())
						throw ParseException(ERR("File header badly formed -  vector variable identifier repeated: " + ret->getIdentifier()));
				}
				continue;
			}
			break;
		}
		//after all, check if each $scope had matching $upscope
		if(scopes.size() != 0)
		    throw ParseException(ERR("File header contains too few $upscope keywords"));
		
		std::string token1;
		istream >> token1;
		//header should terminate with "$enddefinitions $end"
		if(!(token == "$enddefinitions" && token1 == "$end"))
			throw ParseException(ERR("File header contains trash data"));
		return header;
	}
	
	std::string VCDParser::readOneDump(std::ifstream& inFile_) const throw(ParseException) {
		std::string ret, token;
		bool firstHashOccured = false;

		while(inFile_.good()) { 
			inFile_ >> token;
			if(token.at(0) == '#' && token.length() > 1) {
				bool digitsOnly = true;
				for(unsigned i=1; i<token.length(); ++i) {
					if(!isdigit(token.at(i)))
						digitsOnly = false;
				}
				if(digitsOnly == true) {
					if(firstHashOccured == false) {
						firstHashOccured = true;
						ret += token + " ";
					} else {
						for(unsigned i=0; i<=token.length(); ++i)
							inFile_.unget();
						break;
					}
				} else {
					ret += token + " ";
				}
			} else {
				ret += token + " ";
			}
		/*
			getline(inFile_, line);
			if(line.length() == 0)
				continue;
			if(line.at(0) == '#') {
				smatch match;
				static const regex dumpBeginRegex("#\\d+");
				if(!regex_match(line, match, dumpBeginRegex))
					throw ParseException(ERR("Unknown literal"));
				if(firstHashOccured) { /*the whole dump has been read and we encountered the next one */
				/*	for(unsigned i = 0; i <= line.length(); ++i)
					/*	inFile_.unget(); /* put letters back to the file and read them by the next function call */
					/*oneDump.erase(--oneDump.end());  //remove the last appended character (\n)
					break /*while*/; 
				/*} else {
				    firstHashOccured = true;
				    oneDump += line + '\n';			
				}					
			} else {
				oneDump += line + '\n';
			}*/
		}
		return ret;
	}

	short VCDParser::parseTimescale(const std::string& in) const throw(ParseException) {
		
		short timescale;
		if(in.at(0) != '1')
			throw ParseException(ERR("Bad format of simulation timescale:\'" + in +"\'"));
		short zeros = 0;
		while(in.at(zeros+1) == '0')
			++zeros;
		if(zeros > 2)
			throw ParseException(ERR("Bad format of simulation timescale:\'" + in +"\'"));

		char magnitude;
		if(in.at(zeros + 1) == ' ')
			magnitude = in.at(zeros + 2);
		else
			magnitude = in.at(zeros + 1);
		switch(magnitude) {
			case 's': timescale = 0; break;
			case 'u': timescale = -6; break;
			case 'm': timescale = -3; break;
			case 'n': timescale = -9; break;
			case 'p': timescale = -12; break;
			case 'f': timescale = -15; break;
			default: throw ParseException(ERR("Bad format of simulation timescale:\'" + in +"\'"));
		}
		timescale += zeros;
		return timescale;
	}

	std::string VCDParser::readInHeader(std::ifstream& inFile_) const throw(ParseException) {
		std::string token, hdr;
		bool enddefinitionsOccured = 0;
		while(inFile_.good()) {
			inFile_ >> token;
			hdr.append(" ").append(token);
			if(token == "$enddefinitions")
				enddefinitionsOccured = 1;
			if(token == "$end" && enddefinitionsOccured == 1) /*definitions are finished with lines $enddefinitions $end*/
				break;
		}
		if(inFile_.bad())
			throw ParseException(ERR("Unexpected end of file"));
		return hdr;
	}

	void VCDParser::skipComment(std::ifstream& inFile) const throw(ParseException) {
		std::string line;
		bool commentBegan = false;
		while(inFile.good()) {
			inFile >> line;
			if(line.length() > 0 && line.at(0) == '#') {/*there is no comment in the file*/
				for(unsigned i = 0; i <= line.length() /*all characters and white space*/; ++i)
						inFile.unget(); /* put letters back to the file and read them by the next function call */
				break; 
			}
			if(line == "$comment") /*read the beginning of a comment*/
				commentBegan = true;
			else if(commentBegan == true && line == "$end") /*read the end of a comment -> exit*/ 
				break;
		}
		if(inFile.bad())
			throw ParseException(ERR("Unexpected end of file"));	
	}

	void VCDParser::parseValueDump(shared_ptr<VCDHeader>& header, const std::string oneDump) const throw(ParseException) {
		std::istringstream istream;
		std::string token, token1;
		STime dumpTime(0,0);
		char tokenFirstChar;
		bool endExpected = 0;
		istream.str(oneDump);
		static const char* keywords[] = {"$dumpon", "$dumpall", "$dumpoff", "$dumpvars"};
		short timescale = header->getTimescale();
		istream >> token;
		
		///value dump must start with timestep definition
		if(token.at(0) == '#') {
			dumpTime = STime(fromString<long>(std::string(++token.begin(), token.end())), timescale); 
			/**skip '#' at the first position */
		} else {
			throw ParseException(ERR("Expected timestep definition but got: \'" + token + "\'")); 
		}
		
		/** In this function there is 'while' and 'for' block.
		 * The former reads the beginning of a single value dump and checks for presence of keywords
		 *.If sth other is encountered, then the control is passed to the 'for' block 
		 */
		while(true) {
			istream >> token;
			
			if((token == keywords[0]) | (token == keywords[1]) | (token == keywords[2]) | (token == keywords[3])){ //a keyword must have been reached
				if(endExpected)
				    throw ParseException(ERR("Encountered unexpected keyword: " + token));
				endExpected = true;
				continue;
			} else 
			if(token == "$end") {
				if(endExpected == true)
					return;
				else
					throw ParseException(ERR("Encountered unexpected $end keyword"));
			} else { /* some strange line encountered - it is probably value definition */
			    break; 
			}
        }
        
        /** This for block reads value entries one after the other, sanitizes
         * it and adds to an appropriate list
         */
		tokenFirstChar = token.at(0);
        for(;;){
			if(tokenFirstChar == 'b') { /* we probably found a vector value */
			    istream >> token1;
			    std::string value = std::string(token.begin()+1, token.end()); 
			    std::string vcdid = token1; 
			    
			    std::map<std::string, shared_ptr<VectorVar> >::iterator it = header->getVectors().find(vcdid); 
			    if(it == header->getVectors().end())
					throw ParseException(ERR("Unknown variable identifier in value dump section: " + vcdid));
				
				/** check if value isn't longer than the vector */
				if(it->second->getLength() < value.length())
					throw ParseException(ERR("Invalid vector value length of " + value));
				/** expand and save value */
				VectorVar::value_t vectorValueVec = expandVectorValue(value, it->second);
				it->second->addTrace(dumpTime, VectorVar::value_t(vectorValueVec));
			} else /** probably a scalar value */
			if((tokenFirstChar == '1') | (tokenFirstChar == '0') | (tokenFirstChar == 'z') | (tokenFirstChar == 'Z') 
				| (tokenFirstChar == 'x') | (tokenFirstChar == 'X')) {
			    std::string vcdid( token.begin()+1, token.end());
			    std::map<std::string, shared_ptr<ScalarVar> >::iterator it = header->getScalars().find(vcdid);
				
				if(it == header->getScalars().end()) 
					throw ParseException(ERR("Unknown variable identifier in value dump section:" + vcdid));
				it->second->addTrace(dumpTime, ScalarVar::value_t(token.at(0)));			
			} else {
			    break /* for */;
			}
			    
			/** fetch the next line, skip blank lines */
			if(istream.good()) {
				istream >> token;
				tokenFirstChar = token.at(0);
			} else {
				return;
			}
		} /*for*/
		
		if((token != "$end" && endExpected == true) || (token == "$end" && endExpected == false)) /* last read line wasnt ''$end'' - error */
			throw ParseException(ERR("encountered unexpected keyword: " + token));
	}
	inline VectorVar::value_t VCDParser::expandVectorValue(const std::string& vectorValueStr, shared_ptr<VectorVar> vecPtr) const {
		std::vector<char> vectorValueVec;
		vectorValueVec.resize(vecPtr->getLength());
		/*
		for now we have value dump in string in vectorValueStr
		it can be for instance x101
		if the vector is 8 bits long then the value should be expanded to xxxxx101
		*/
		
		/* xxxxx... */
		fill_n(vectorValueVec.begin(), vecPtr->getLength()-vectorValueStr.length()+1, vectorValueStr.at(0));			
		/* xxxxx101 */
		copy_backward(++vectorValueStr.begin(),vectorValueStr.end(),vectorValueVec.end());
		return vectorValueVec;
	}
	inline void VCDParser::trimLine(std::string& in) const {
		int i;
		if(in.length() == 0)
			return;
		for(i = in.length()-1; i >= 0; --i) {
			if( in.at(i) != ' ' )
				break;	
		}
		in.resize(i+1);
	}
}

