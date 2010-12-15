#ifndef _TRACE_H_
#define _TRACE_H_

#include <utility>
namespace VcdCT {
	/**
		Template class used for representing traces.
		At first std::pair was used but then I noticed I get confused
		when constantly using pair.first and pair.second, which doesn't
		tell much
	*/
	template <typename time_t, typename value_t> class Trace : private std::pair<time_t, value_t> {
	public:
		explicit Trace(const time_t& time, const value_t& value) {this->first = time; this->second = value;}
		time_t getTime() const {return this->first;}
		value_t getValue() const {return this->second;}
	};

	template<typename time_t, typename value_t> Trace<time_t, value_t> make_trace(const time_t& time, const value_t& value) {return Trace<time_t, value_t>(time, value); }
}

#endif

