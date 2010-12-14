#include <getopt.h>
#include <iostream>
#include <fstream>
#include <string>
#include <stdexcept>
#include "common.h"
#include "fst_writer.h"
#include "vcd_header.h"
#include "vcd_parser.h"
#include "vcd_comparator.h"
#include "parse_exception.h"
#include "file_handling_exception.h"

using namespace VcdCT;

static bool check(const std::string& infileName) throw(FileHandlingException, ParseException);
static bool print(const std::string& infileName) throw(FileHandlingException, ParseException);
static shared_ptr<VCDHeader> compare(const std::string& infile1Name, 
										const std::string& infile2Name, 
											const std::string& ofileName) 
												throw(FileHandlingException, ParseException);
/**
  Prints error message when program is invoked with invalid arguments or with --help
*/
static void printUsage() {
	std::cout << "VCD Compare Tool version " << VERSION << std::endl <<
			"Usage: " << 
			"vcdct [OPTION] [FILE]...\n" <<
			"options:\n" <<
			"\t-k,	--check FILE [FILE ...]\t\tCheck syntax of listed file(s).\n" << 
			"\t-c,	--compare FILE FILE\t\tCompare two given files.\n" <<
			"\t-p,	--print FILE [FLE ...]\t\tPrint content of file sorted by variable.\n" <<
			"\t-o,	--output FILE\t\t\tSet comparison output. By default output goes to out.fst.\n" <<
			"\t-h,	--help\t\t\t\tPrint this message." << std::endl;
}

int main(int argc, char** argv) {
	
	/** Stream synchronization is disabled in order to make
		operation on stream faster
	*/
	std::ios_base::sync_with_stdio(0);
	std::string infile1Name, infile2Name, ofileName;
	bool isCompare, isCheck, isOutput, isPrint;
	isCompare = isCheck = isOutput = isPrint = 0;
	ofileName = "out.fst";
	int c;
	
	while(1) {
		int optionIndex = 0;
		static struct option long_options[] =
			{
				{"compare", no_argument, 0, 'c'},
				{"check", no_argument, 0, 'k'},
				{"print", no_argument, 0, 'p'},
				{"output", required_argument, 0, 'o'}, 
				{"help", no_argument, 0, 'h'},
				{0,0,0,0} //end delimiter
			};
		c = getopt_long(argc, argv, "kcpo:h", long_options, &optionIndex);
		if(c == -1) { /* nor more args */
			break;
		} 
		
		switch(c) { /* check options and mark option flags */
			case 'k': isCheck = 1; break;
			case 'c': isCompare = 1; break;
			case 'p': isPrint = 1; break;
			case 'o': isOutput = 1; ofileName = std::string(optarg); break;
			case 'h': printUsage(); return 0;
			case '?': printUsage(); return 0;
			default:
				/* unreachable */
				break;
		}
	} //while(1)	
	
	/* Only one of checked options is possible at a time */
	if(isCompare + isCheck + isPrint > 1) {
		std::cout << "Error: too many options selected." << std::endl;
		printUsage();
		return 1;
	}
	/* At least one of these options must be given */
	if(isCompare + isCheck + isPrint < 1) {
		std::cout << "Error: too few options selected." << std::endl;
		printUsage();
		return 1;
	}
	int numberOfFiles = argc-optind;
	/* Comparison requires two files as arguments */
	if(isCompare && numberOfFiles != 2) {
		std::cout << "Error: comparison requires two files." << std::endl;
		printUsage();
		return 1;
	}
	if(isCheck) {
		if(numberOfFiles == 0) {
			std::cout << "Error: check options requires at least one file." << std::endl;
			printUsage();
			return 1;
		}
		
		bool fail = false;
		/* check syntax for each of files listed as argument */
		while(optind < argc) {
			std::string filename = argv[optind++]; 
			try{
				check(filename);
				std::cout << "File " << filename << " formed correctly." << std::endl;
				std::cout << "----------------------------" << std::endl;
			} catch(ParseException& exception) {
				fail = true;
				std::cerr << "Error while parsing file: "<< filename << "\n" << exception.what() << std::endl;
			} catch(FileHandlingException& exception) {
				fail = true;
				std::cerr << "Error while parsing file: "<< filename << "\n" << exception.what() << std::endl;
			} catch(std::exception& exception) {
				fail = true;
				std::cerr << "Error while parsing file: "<< filename << "\n" << exception.what() << std::endl;
			}
		}
		if(fail == false) {
			std::cout << "All files formed correctly." << std::endl;
			return 0;  
		}
	}
	if(isCompare) {
		infile1Name = argv[optind];
		infile2Name = argv[optind+1]; 

		try {
		  compare(infile1Name, infile2Name, ofileName);    
		} catch(ParseException& exception) {
		  std::cerr << "Exception while parsing input file:\n" << exception.what() << std::endl;
		  return 1;
		} catch(FileHandlingException& exception) {
		  std::cerr << "Exception while handling input file:\n" << exception.what() << std::endl;
			return 1;
		} catch(std::exception& exception) {
			std::cerr << "Exception: " << exception.what() << std::endl;
			return 1;
		}
		return 0;           
	}
	if(isPrint) {
		if(numberOfFiles < 1) {
		  std::cout << "Error: print requires at least one file." << std::endl;
		  printUsage();
		  return 1;
		}
		while(optind < argc) {
			std::string filename = argv[optind++];
			try{
				std::cout << "File: " << filename << std::endl;
				print(filename);
			} catch(ParseException& exception) {
				std::cerr << "Exception while parsing input file:\n" << exception.what() << std::endl;
				continue;
			} catch(FileHandlingException& exception) {
				std::cerr << "Exception while handling input file:\n" << exception.what() << std::endl;
				continue;
			} catch(std::exception& exception) {
				std::cerr << "Exception: " << exception.what() << std::endl;
				continue;
			}
		}
		return 0;
	}
	return 0;
}
static bool print(const std::string& infileName) 
	throw(FileHandlingException, ParseException) {
	std::ifstream infile;
	infile.open(infileName.c_str(), std::ifstream::in);
  
	if(!infile.is_open())
		throw FileHandlingException(ERR("Error while opening input file."));
	VCDParser parser;
	
	std::string hdr = parser.readInHeader(infile);
	shared_ptr<VCDHeader> ph = parser.parseHeader(hdr);
	parser.skipComment(infile);
	
	while(infile.good()) {
		std::string dump = parser.readOneDump(infile);
		parser.parseValueDump(ph, dump);
	}
	std::cout << "SCALARS" << std::endl;
	for(std::map<std::string,shared_ptr<ScalarVar> >::const_iterator it = ph->getScalars().begin(); it != ph->getScalars().end(); ++it)
		std::cout << *(it->second) << std::endl;
	std::cout << "VECTORS" << std::endl;
	for(std::map<std::string,shared_ptr<VectorVar> >::const_iterator it = ph->getVectors().begin(); it != ph->getVectors().end(); ++it)
		std::cout << *(it->second) << std::endl;
	/* if an exception has not been thrown, before then everything is ok with the files */	
	infile.close();
	return true;
}
static bool check(const std::string& infileName) 
	throw(FileHandlingException, ParseException) {
	std::ifstream infile;
	infile.open(infileName.c_str(), std::ifstream::in);
  
	if(!infile.is_open())
		throw FileHandlingException(ERR("Error while opening input file."));
	VCDParser parser;
	
	std::string hdr = parser.readInHeader(infile);
	shared_ptr<VCDHeader> ph = parser.parseHeader(hdr);
	parser.skipComment(infile);
	
	while(infile.good()) {
		std::string dump = parser.readOneDump(infile);
		parser.parseValueDump(ph, dump);
	}
	/* if an exception has not been thrown, before then everything is ok with the files */	
	infile.close();
	return true;
}
	

static shared_ptr<VCDHeader> compare(const std::string& infile1Name, const std::string& infile2Name, 
			const std::string& ofileName) throw(FileHandlingException, ParseException)  {
	
	std::ifstream infile1, infile2;
	//std::ofstream ofile;
	infile1.open (infile1Name.c_str(), std::ifstream::in);
	
	if(!infile1.is_open()) {
		throw FileHandlingException(ERR("Error while opening input file: " + infile1Name + ".\nBe sure it exists and has appropriate access rights."));
	}
	infile2.open (infile2Name.c_str() , std::ifstream::in);
	if(!infile2.is_open()) {
		throw FileHandlingException(ERR("Error while opening input file: " + infile2Name + ".\nBe sure it exists and has appropriate access rights."));
	}
	VCDParser parser;

	std::string hdr1 = parser.readInHeader(infile1);
	std::string hdr2 = parser.readInHeader(infile2);
	shared_ptr<VCDHeader> ph1 = parser.parseHeader(hdr1);
	shared_ptr<VCDHeader> ph2 = parser.parseHeader(hdr2);
	if(ph1->getScalars().size() == 0 && ph2->getScalars().size() == 0 && 
		ph1->getVectors().size() == 0 && ph2->getVectors().size() == 0) {
		throw std::runtime_error("No valuable data in both input files.");
	}
	
	//output file is created by FSTWriter::writeDwonFST
	parser.skipComment(infile1);
	parser.skipComment(infile2);
	while(infile1.good()) {
		std::string dump = parser.readOneDump(infile1);
		parser.parseValueDump(ph1, dump);
	}
	while(infile2.good()) {
		std::string dump = parser.readOneDump(infile2);
		parser.parseValueDump(ph2, dump);
	}
	shared_ptr<VCDHeader> comparisonResult = VCDComparator::getInstance().compareFiles(ph1,ph2);
	FSTWriter f(ofileName);
	f.writeDownFST(comparisonResult);
	
	infile1.close();
	infile2.close();

  return comparisonResult;
}
