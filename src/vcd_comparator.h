#ifndef _VCD_COMPARATOR_H_
#define _VCD_COMPARATOR_H_

#include "common.h"
#include "scalar_var.h"
#include "vcd_header.h"
#include "vector_var.h"
#include "container_variable.h"

namespace VcdCT {
	/** The class performs with its one public memeber function a comparison of two vcd files */
	class VCDComparator {
	public:
		static VCDComparator& getInstance() {
			static VCDComparator instance;
			return instance;
		}
		/** This functions takes two files as VCDHeader objects and does comparison
			of matching variables. Variables are matching when they are of the same type (in the verilog
			meaning), have the same length, reference (i.e. names) and are defined in the same scopes. 
			For comparison the function compareVariables is used.
		*/
		shared_ptr<VCDHeader> compareFiles(shared_ptr<VCDHeader> h1, shared_ptr<VCDHeader> h2);
	private:		
		/** Function compares two scalar variable values. It is attached to vector<char> as
			VectorVar::value_t because of the usage of compareValues() for scalars.
			\return returned value depends on both compared values. If at least one of them is
			undefined, then it return 'z'. If both are defined but are diferent, then it return '0'.
			If they are equal, then the result is '1'.
		*/
		static ScalarVar::value_t compareValues(ScalarVar::value_t v1, ScalarVar::value_t v2) { 
			return ScalarVar::value_t(toString(v1 == v2).c_str()[0]); 
		}
		/** Function compares two vector variable values. It iterates over variable's collections
			and uses compareValues() for comparison of each iterated pair of objects.
			For the time being it is attached to char as ScalarVar::value_t.
		*/
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
		
		/** This template function is used for comparing both scalar and vector variables.
			\param first first variable
			\param second second variable
			\param ret variable where the result is to be put
			*/
		template<typename var>
		shared_ptr<var> compareVariables(shared_ptr<var> first, shared_ptr<var> second, shared_ptr<var> ret);
		template<typename time_t>
		inline time_t minTime(time_t t1, time_t t2) { return t1>t2?t2:t1;}
	};

}
#endif

