#ifndef _FST_WRITER_H_
#define _FST_WRITER_H_

#include <string>
#include <fstream>
#include "file_handling_exception.h"
#include "vcd_header.h"

namespace VcdCT {
	class FSTWriter {
	public:
		FSTWriter(std::string fileName) : fileName_(fileName) {}
		void writeDownFST(shared_ptr<VCDHeader>& header);
	private:
		std::string fileName_;
		unsigned int vcdid_hash(char *s);
	};
}
	
#endif
