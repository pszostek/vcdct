#include <iostream>
#include "variable.h"

namespace VcdCT {
	std::ostream& operator<<(std::ostream& stream, Variable::ScopeType& vec) {
		switch(vec) {
			case Variable::MODULE: stream << "module"; break;
			case Variable::TASK:	stream << "task"; break;
			case Variable::FUNCTION: stream << "function"; break;
			case Variable::BEGIN: stream << "begin"; break;
			case Variable::FORK: stream << "fork"; break;
		}
		return stream;
	}
} //namespace
