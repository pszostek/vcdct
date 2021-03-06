#ifndef _VECTORVAR_H_
#define _VECTORVAR_H_

#include <string>
#include <list>
#include <utility>
#include <vector>
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

namespace VcdCT {	
	class VectorVar : public ContainerVariable<STime, std::vector<char> > {
	public:
		typedef STime time_t;
		typedef std::vector<char> value_t;
		typedef Trace<time_t,value_t > trace_t;
		VectorVar(VarTypeCode::VarTypeEnum varTypeCode, std::string varIdent, std::string varReference, unsigned length) : 
			ContainerVariable<time_t, value_t>(varTypeCode,varIdent,varReference),length_(length) {};
		~VectorVar() {};
		void addTrace(const time_t& time, const value_t& val) {
		  this->addTrace(make_trace(time, val));
		}
		/**
			The function adds the argument to the list of
			kept traces
		*/
		void addTrace(const trace_t& newTrace) {
		  if(this->empty()) {
			this->push_back(newTrace);
		  } else if(this->back().getValue() != newTrace.getValue() && this->back().getTime() != newTrace.getTime()) {
			this->push_back(newTrace);
		  }
		}
		void addTrace(const time_t& time,const char& val) {
		  this->addTrace(time, std::vector<char>(this->getLength(),val));
		}
		virtual short getLength() const { return length_; }
		friend std::ostream& operator<<(std::ostream& stream,VectorVar& vec);
	private:
		const short length_;
	};
}

#endif //_VECTORVAR_H_

