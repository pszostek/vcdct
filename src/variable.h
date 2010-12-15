#ifndef _VARIABLE_H_
#define _VARIABLE_H_

#include <string>
#include <vector>
#include <utility>
#include "var_type_code.h"
#include "trace.h"

namespace VcdCT {
	/** Abstract class representing a variable in general. It is derived
		by ContainerVariable. It keeps attributes that are common for both
		scalar and vector variables
	*/
	class Variable{
	public:
		typedef enum ScopeType {MODULE = 0, TASK, FUNCTION, BEGIN, FORK} ScopeType;
		std::string getReference() const { return varReference_; }
		std::string getIdentifier() const { return varIdent_; }
		std::vector< std::pair<ScopeType, std::string > >  getScopes() const {return scopes_; }
		void setScopes(std::vector<std::pair<ScopeType, std::string> > scopes) { scopes_ = scopes; }
		VarTypeCode::VarTypeEnum getVarTypeCode() const { return varTypeCode_; } 
		Variable(VarTypeCode::VarTypeEnum varTypeCode, std::string varIdent, std::string varReference) : varTypeCode_(varTypeCode), varIdent_(varIdent), 
									varReference_(varReference) {};
		virtual ~Variable() {}
		virtual short getLength() const = 0; 
	protected:
		/** One of Verilog types - listed in VarType enum (see var_type_code.h) */
		VarTypeCode::VarTypeEnum varTypeCode_;
		/** Variable identifier used in dumpfile */
		std::string varIdent_;
		/** Reference - name of the variable */
		std::string varReference_;
		/** List of variable scopes, as defined in .vcd file */
		std::vector< std::pair<ScopeType, std::string /*name*/ > > scopes_;
		
	};
	std::ostream& operator<<(std::ostream& stream, Variable::ScopeType& vec);
} //namespace

#endif //_VARIABLE_H_

