#ifndef _CONTAINER_VARIABLE_H_
#define _CONTAINER_VARIABLE_H_

#include <string>
#include <vector>
#include <utility>
#include "var_type_code.h"
#include "trace.h"
#include "variable.h"

namespace VcdCT {
	/** Virtual template class that represents containing vector of traces
		ScalarVar and VectorVar derive from it
	*/
	template<typename time_t, typename value_t>
	class ContainerVariable : public std::vector<Trace<time_t, value_t> >, public Variable {
	public:
		typedef Trace<time_t, value_t> trace_t;
		typedef enum Value {zero, one, x, z} Value;
		ContainerVariable(VarTypeCode::VarTypeEnum varTypeCode, std::string varIdent, std::string varReference) : Variable(varTypeCode, varIdent, varReference){};
		virtual ~ContainerVariable() {};
		/** This function has to be implemented in concrete classes
			\return The length of variable's trace is returned
		*/
		virtual short getLength() const = 0; 
		void addTrace(trace_t newTrace) {
			if(this->empty()) {
				this->push_back(newTrace);
			} else if(this->back().getValue() != newTrace.getValue() && this->back().getTime() != newTrace.getTime()) {
				this->push_back(newTrace);
			} 
		}
		void addTrace(time_t time, value_t value) {
			Trace<time_t,value_t> t = Trace<time_t,value_t>(time,value);
			addTrace(t);
		}
	protected:
		/* One of Verilog types - listed in VarType enum} */
		VarTypeCode::VarTypeEnum varTypeCode_;
		/* Variable identifier used in dumpfile */
		std::string varIdent_;
		/* Reference - name of the variable */
		std::string varReference_;
		/* Scope of variable in format scope1.scope2.scope3.(...) */
		std::vector< std::pair<Variable::ScopeType, std::string /*name*/ > > scopes_;
	};
}

#endif //_CONTAINER_VARIABLE_H_
