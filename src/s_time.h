#ifndef _S_TIME_H_
#define _S_TIME_H_

#define min(x,y) ((x) < (y) ? (x) : (y))
#define max(x,y) ((x) > (y) ? (x) : (y))

/** Class for describing simulation time */
namespace VcdCT {
	double pow10(short num) { if(num == 0) return 1; else return 10*pow10(num-1);  }
	
	class STime {
	public:
		friend bool operator<(const STime& t1, const STime& t2);
		friend bool operator>(const STime& t1, const STime& t2);
		friend bool operator==(const STime& t1, const STime& t2);
		friend bool operator!=(const STime& t1, const STime& t2);
		friend bool operator<=(const STime& t1, const STime& t2);
		friend bool operator>=(const STime& t1, const STime& t2);
		STime(unsigned long sig, short exp) { significand = sig; exponent = exp; }
		/** Simulation time is expressed as time that passed from simulation start.
			Its form is a*10^(-b)[s],
			where
				a is significand 
				b is exponent*/
		/** Significand is taken from #xxx statement, that is given on the beginning
			of every dump */
		unsigned long significand;
		/** exponent value is taken from timescale statement */
		short exponent;	
	};
	bool operator<(const STime& t1, const STime& t2) {
		if(t1.exponent < t2.exponent && t1.significand < t2.significand)
			return true;
		else
		if(t1.exponent > t2.exponent && t1.significand > t2.significand)
			return false;
		else
		if(t1.exponent == t2.exponent)
			return t1.significand < t2.significand;
		else
		if(t1.significand == t2.significand)
			return t1.significand < t2.significand;
		else {
			if(t1.significand < t2.significand) {
				return ((double(t2.significand)/pow10(t1.exponent - t2.exponent)) > t1.significand);
			}
			else { //t1.significand > t2.significand
			}
		}
	}
	bool operator>(const STime& t1, const STime& t2) {
		if(t1.exponent < t2.exponent && t1.significand < t2.significand)
			return false;
		else
		if(t1.exponent > t2.exponent && t1.significand > t2.significand)
			return true;
		else
		if(t1.exponent == t2.exponent)
			return t1.significand < t2.significand;
		else
		if(t1.significand == t2.significand)
			return t1.significand < t2.significand;
		else {//////////////////////////////////////////////////////////////////////////ELABORATE
		}
	}
	bool operator==(const STime& t1, const STime& t2) {
		return (t1.significand == t2.significand &&
				t1.exponent == t2.exponent); 
	}
	bool operator!=(const STime& t1, const STime& t2) {
		return !(t1 == t2);
	}
	bool operator<=(const STime& t1, const STime& t2) {
		return ((t1 == t2) || (t1 < t2));
	}
	bool operator>=(const STime& t1, const STime& t2) {
		return ((t1 == t2) || (t1 > t2));
	}
}
#endif
