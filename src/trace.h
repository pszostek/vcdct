#ifndef _TRACE_H_
#define _TRACE_H_

#include <utility>
namespace VcdCT {
	template <typename time_t, typename value_t> class Trace : private std::pair<time_t, value_t> {
	public:
		explicit Trace(const time_t& time, const value_t& value) {this->first = time; this->second = value;}
		time_t getTime() const {return this->first;}
		value_t getValue() const {return this->second;}
	};

	template<typename time_t, typename value_t> Trace<time_t, value_t> make_trace(const time_t& time, const value_t& value) {return Trace<time_t, value_t>(time, value); }
}

#endif

