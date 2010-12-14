#ifndef _SCALARVAR_H_
#define _SCALARVAR_H_

#include <string>
#include <list>
#include <vector>
#include <iostream>
#include <utility>
#include <iostream>
#ifdef BOOST_SHARED_PTR_HPP
  #include <boost/shared_ptr.hpp>
#else
  #include "boost/shared_ptr.hpp"
#endif
#ifdef BOOST_FOREACH_HPP
  #include <boost/foreach.hpp>
#else
  #include "boost/foreach.hpp"
#endif
#include "common.h"
#include "container_variable.h"
#include "trace.h"

using boost::shared_ptr;

namespace VcdCT {	
	class ScalarVar : public ContainerVariable<unsigned long, char> {
	public:
		typedef unsigned long time_t;
		typedef char value_t;
		typedef Trace<time_t, value_t> trace_t;
		ScalarVar(VarTypeCode::VarTypeEnum varType, std::string varIdent, std::string varReference) : ContainerVariable<time_t, value_t>(varType,varIdent,varReference) {};	
		virtual short getLength() const {return 1;}
		virtual ~ScalarVar() {};		
		
		void addTrace(time_t time, value_t val) {
		  Trace<time_t, value_t> newTrace(time,val);
		  this->addTrace(newTrace);
		}
		void addTrace(trace_t newTrace) {
		  if(this->empty()) {
			this->push_back(newTrace);
		  } else if(this->back().getValue() != newTrace.getValue() && this->back().getTime() != newTrace.getTime()) {
			this->push_back(newTrace);
		  }
		}
// 		void addTrace(time_t time, char val) {
// 		  this->addTrace(time, value_t(val));
// 		}
		friend std::ostream& operator<<(std::ostream& stream, ScalarVar& vec);
	private:
	};
}

#endif //_SCALARVAR_H_

