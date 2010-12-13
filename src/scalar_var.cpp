#include "scalar_var.h"

namespace VcdCT {
	std::ostream& operator<<(std::ostream& stream, ScalarVar& scalar) {
		stream << "Reference:\t" << scalar.getReference() << "\n" << 
				  "Identifier: \t" << scalar.getIdentifier() << std::endl;
				  
		stream << "Scopes:\n";
		typedef std::pair<ScalarVar::ScopeType, std::string> scopes_t; /* BOOST_FOREACH doesn't accept templates in () */
		foreach(scopes_t s, scalar.getScopes()) {
		    stream << "\t" << s.first << " " << s.second << std::endl;
		}
		foreach(ScalarVar::trace_t trace, scalar) {
			stream << "#" << trace.getTime() << ":" << trace.getValue();
			stream << std::endl;
		}
	stream << "-------------------------";
	return stream;	
	}
}
  