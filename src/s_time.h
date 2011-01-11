#ifndef _S_TIME_H_
#define _S_TIME_H_

#include <iostream>
#include <ostream>

#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))


/** Class for describing simulation time */
namespace VcdCT {
	inline double pow10(const short& num) { if(num == 0) return 1.0; else return 10.0*pow10(num-1);  }
	
	class STime {
	public:
		explicit STime(unsigned long sig, short exp) { significand = sig; exponent = exp; }
		/** Simulation time is expressed as time that passed from simulation start.
			Its form is a*10^(-b)[s],
			where:
				a is significand,
				b is exponent
		*/
		friend bool operator<(const STime& t1, const STime& t2);
		friend bool operator>(const STime& t1, const STime& t2);
		friend bool operator!=(const STime& t1, const STime& t2);
		friend bool operator==(const STime& t1, const STime& t2);
		friend bool operator<=(const STime& t1, const STime& t2);
		friend bool operator>=(const STime& t1, const STime& t2);
		/** Significand is taken from #xxx statement, that is given on the beginning
			of every dump */
		unsigned long significand; //no negative time
		/** exponent value is taken from timescale statement */
		short exponent;	
	};
}	
#endif
