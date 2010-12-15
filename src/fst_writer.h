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
		/** The function is partially cope-paste from GTKWave's FST writing routine.
			It writes down header attributes and variables definitions. Subsequently all
			value dumps (for both scalars and vectors) are written down while correct
			time order is kept
		*/
		void writeDownFST(shared_ptr<VCDHeader>& header);
	private:
		std::string fileName_;
		unsigned int vcdid_hash(char *s);
	};
}
	
#endif
