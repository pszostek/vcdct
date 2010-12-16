#ifndef _SCALARVAR_H_
#define _SCALARVAR_H_

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <utility>
#include <iostream>
#ifdef HAVE_BOOST_SHARED_PTR_HPP
  #include <boost/shared_ptr.hpp>
#else
  #include "boost/shared_ptr.hpp"
#endif
#include "common.h"
#include "container_variable.h"
#include "s_time.h"
#include "trace.h"

using boost::shared_ptr;

namespace VcdCT {	
	/** The class represents Scalar variable, which is one of two types
		that are present in VCD files
	*/
	class ScalarVar : public ContainerVariable<STime, char> {
	public:
		typedef STime time_t;
		typedef char value_t;
		typedef Trace<time_t, value_t> trace_t;
		ScalarVar(VarTypeCode::VarTypeEnum varType, std::string varIdent, std::string varReference) : ContainerVariable<time_t, value_t>(varType,varIdent,varReference) {};	
		/** It is a implementation of pure virtual function from ContainerVariable.
			For scalars 1 is always returned
		*/
		virtual short getLength() const {return 1;}
		virtual ~ScalarVar() {};		
		
		/**
			The function adds the argument to the list of
			kept traces
		*/
		void addTrace(time_t time, value_t val) {
		  this->addTrace(make_trace(time, val));
		}
		void addTrace(trace_t newTrace) {
		  if(this->empty()) {
			this->push_back(newTrace);
		  } else if(this->back().getValue() != newTrace.getValue() && this->back().getTime() != newTrace.getTime()) {
			this->push_back(newTrace);
		  }
		}
		friend std::ostream& operator<<(std::ostream& stream, ScalarVar& vec);
	private:
	};
}

#endif //_SCALARVAR_H_

