#ifndef _VCD_COMPARATOR_H_
#define _VCD_COMPARATOR_H_

#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include "common.h"
#include "scalar_var.h"
#include "vcd_header.h"
#include "vector_var.h"
#include "container_variable.h"

using boost::lexical_cast;

namespace VcdCT {
	class VCDComparator {
	public:
		static VCDComparator& getInstance() {
			static VCDComparator instance;
			return instance;
		}
		shared_ptr<VCDHeader> compareFiles(shared_ptr<VCDHeader> h1, shared_ptr<VCDHeader> h2);
	private:		
		static ScalarVar::value_t compareValues(ScalarVar::value_t v1, ScalarVar::value_t v2) { 
			return ScalarVar::value_t(lexical_cast<char>(v1 == v2)); 
		}
		static VectorVar::value_t compareValues(VectorVar::value_t v1, VectorVar::value_t v2) {
		    const VectorVar::value_t::const_iterator end = v1.end();
		    VectorVar::value_t ret;
		    
		    VectorVar::value_t::const_iterator it1 = v1.begin();
		    VectorVar::value_t::const_iterator it2 = v2.begin();
		    for(;it1 != end; ++it1, ++it2)
		        ret.push_back(compareValues(*it1, *it2));
		    return ret;
		}
		
		VCDComparator() {};
		VCDComparator(const VCDComparator&);
		
		template<typename var>
		shared_ptr<var> compareVariables(shared_ptr<var> first, shared_ptr<var> second, shared_ptr<var> ret);
		template<typename time_t>
		time_t minTime(time_t t1, time_t t2) { return t1>t2?t2:t1;}
	};

}
#endif

