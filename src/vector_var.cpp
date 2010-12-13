#include "vector_var.h"

namespace VcdCT {
	std::ostream& operator<<(std::ostream& stream, VcdCT::VectorVar& vec) {
		stream << "Reference:\t" << vec.getReference() << "\n" << 
					"Identifier: \t" << vec.getIdentifier() << std::endl;
	
		stream << "Scopes:" << std::endl;
		typedef std::pair<Variable::ScopeType, std::string> scopes_t; /* BOOST_FOREACH doesn't accept templates in () */
		foreach(scopes_t s, vec.getScopes()) {
		    stream << "\t" << s.first << " " << s.second << std::endl;
		}
		foreach(VectorVar::trace_t trace, vec) {
			stream << "#" << trace.getTime() << ":";
			foreach(char ch, trace.getValue()) {
					stream << ch;
			}
			stream << std::endl;
		}
		stream << "-------------------------";
		return stream;
	}
  std::ostream& operator<<(std::ostream& stream, std::vector<char> vec) {
	  for(int i=0; i<vec.size(); ++i)
		 stream << vec.at(i);
	  stream << std::endl;
	  return stream;
  }
}

