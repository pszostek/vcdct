#ifndef _VCDHEADER_H_
#define _VCDHEADER_H_

#include <string>
#include <iterator>
#include <vector>
#include <map>
#ifdef HAVE_BOOST_SHARED_PTR_HPP
  #include <boost/shared_ptr.hpp>
#else
  #include "boost/shared_ptr.hpp"
#endif
#include "scalar_var.h"
#include "variable.h"
#include "vector_var.h"

#include "trace.h"

using boost::shared_ptr;

namespace VcdCT {
	/** The class is used to represent data stored in vcd file, it means: statements
		from the header (version, timescale, date), variables declarations ($var .. $end statements)
		and lists of scalars and vectors stored in two separate containters
	*/
	class VCDHeader {
	public:
		std::string getVersion() const {return version_;}
		void setVersion(std::string version) {version_ = version;}
		short getTimescale() const {return timescale_;}
		void setTimescale(int timescale) {timescale_ = timescale;}
		std::string getTDate() const {return date_;}
		void setDate(std::string date) {date_ = date;}
		/**
			\return Returns reference to map of collected vector. The keys are variable references,
			the values are pointers to vector variables
		*/
		std::map<std::string,shared_ptr<VectorVar> >& getVectors() {return vectors_;}
		/**
			\return Returns reference to map of collected scalars. The keys are variable references,
			the values are pointers to scalar variables
		*/
		std::map<std::string,shared_ptr<ScalarVar> >& getScalars() {return scalars_;}	
		
		/** Add scalar to held scalar conatiner.*/
		std::pair<std::map<std::string, shared_ptr<ScalarVar> >::iterator, bool> addScalar(shared_ptr<ScalarVar> var) {
			return scalars_.insert(make_pair(var->getIdentifier(), var));
		}		
		/** Add vector to held vector container */
		std::pair<std::map<std::string,shared_ptr<VectorVar> >::iterator, bool> addVector(shared_ptr<VectorVar> var) {
			return vectors_.insert(make_pair(var->getIdentifier(), var));
		}
	private:
		/** Version from vcd file */
		std::string version_;
		/** Timescale from vcd file in form of exponent of 10, when single timestep expressed in second */
		short timescale_;
		/** Date of simulation from vcd file */
		std::string date_;
		/** Map of file's vectors. The keys are variable references and values are pointers to variables.
			Notice: variable references are stored in both map keys and variables' private members. This
			redundancy should make value dump parsing process more robust
		*/
		std::map<std::string,shared_ptr<VectorVar> > vectors_;
		/** Map of file's strings. The keys are variable references and values are pointers to variables.
			Notice: variable references are stored in both map keys and variables' private members. This
			redundancy should make value dump parsing process more robust
		*/
		std::map<std::string,shared_ptr<ScalarVar> > scalars_;
	};
}

#endif

