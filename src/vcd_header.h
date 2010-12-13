#ifndef _VCDHEADER_H_
#define _VCDHEADER_H_

#include <string>
#include <iterator>
#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include "scalar_var.h"
#include "variable.h"
#include "vector_var.h"

#include "trace.h"

using std::string;
using std::vector;
using boost::shared_ptr;
using std::map;
using std::iterator;
using std::pair;

namespace VcdCT {

	class VCDHeader {
	public:
		std::string getVersion() const {return version_;}
		void setVersion(std::string version) {version_ = version;}
		int getTimescale() {return timescale_;}
		void setTimescale(int timescale) {timescale_ = timescale;}
		std::string getTDate() const {return date_;}
		void setDate(std::string date) {date_ = date;}
		std::map<std::string,shared_ptr<VectorVar> >& getVectors() {return vectors_;}
		std::map<std::string,shared_ptr<ScalarVar> >& getScalars() {return scalars_;}	
		
		std::pair<std::map<std::string, shared_ptr<ScalarVar> >::iterator, bool> addScalar(shared_ptr<ScalarVar> var) {
			return scalars_.insert(make_pair(var->getIdentifier(), var));
		}		
		
		std::pair<std::map<std::string,shared_ptr<VectorVar> >::iterator, bool> addVector(shared_ptr<VectorVar> var) {
			return vectors_.insert(make_pair(var->getIdentifier(), var));
		}
	private:
		std::string version_;
		int timescale_;
		std::string date_;
		long startTime_;
		std::map<std::string,shared_ptr<VectorVar> > vectors_;
		std::map<std::string,shared_ptr<ScalarVar> > scalars_;
	};
}

#endif

