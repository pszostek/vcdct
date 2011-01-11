#ifndef _VCD_COMPARATOR_HPP_
#define _VCD_COMPARATOR_HPP_

#include <list>
#include <string>
#include <vector>
#include <iostream>
#include <utility>
#include <iostream>
#include "common.h"
#include "s_time.h"
#include "var_type_code.h"
#include "trace.h"
#include "vcd_comparator.h"

namespace VcdCT {	
	/*
		Concept:
			Comparison of two values results in:
			1 if both values are the same,
			0 if values are different,
			z if one of the values is undefined.
	*/
	template<typename var>
	shared_ptr<var> VCDComparator::compareVariables(shared_ptr<var> first, shared_ptr<var> second, shared_ptr<var> ret) {
		typename var::const_iterator itFirst = first->begin();
		typename var::const_iterator itSecond = second->begin();	
		
		if(first->begin() == first->end() || second->begin() == second->end()) { //! if at least one of scalars is empty
			if(first->begin() != first->end() || second->begin() != second->end()) { //! if one of them is not empty
				//! take the smaller time and put undefined
				ret->addTrace(minTime(itFirst->getTime(), itSecond->getTime()), typename var::value_t('z')); 
				return ret;
			}
			return ret;
		}
		//! here we know, that both variables are not empty
		if(first->back().getTime() < second->front().getTime()) {  //! no common range - the first ends before the second begins
			for( /*itFirst*/; itFirst != first->end(); ++itFirst) { 
				ret->addTrace(itFirst->getTime(), typename var::value_t('z'));
			} 
			for( /*itSecond*/; itSecond != second->end(); ++itSecond) {
				typename var::value_t t = VCDComparator::compareValues(itSecond->getValue(), first->back().getValue());
				ret->addTrace(itSecond->getTime(), t);
			}
			return ret;
		} else if (second->back().getTime() < first->front().getTime()) { //! no common range - the second ends before the first begins
			for( /*itSecond*/; itSecond != second->end(); ++itSecond) {
				ret->addTrace(itSecond->getTime(), typename var::value_t('z'));
			} 
			for( /*itFirst*/; itFirst != first->end(); ++itFirst) {
				ret->addTrace(itFirst->getTime(), VCDComparator::compareValues(itFirst->getValue(), second->back().getValue()));
			}
			return ret;
		} else { //! there is common range
			typename var::const_iterator itFirst_prev = itFirst;
			typename var::const_iterator itSecond_prev = itSecond;
			if(itFirst->getTime() < itSecond->getTime()) { //! first begins before second
				do {
					ret->addTrace(itFirst->getTime(), 'z'); //! undefined comparison - one variable is not defined at this time
					itFirst_prev = itFirst++;
				} while(itFirst->getTime() < itSecond->getTime());
			} else if(itSecond->getTime() < itFirst->getTime()) { //! second begins before first
				do {
					ret->addTrace(itSecond->getTime(),'z'); //! undefined comparison - one variable is not defined at this time
					itSecond_prev = itSecond++;
				} while(itSecond->getTime() < itFirst->getTime());
			} //else {}
			
			for(;;) {
				if(itSecond == second->end() && itFirst == first->end()) {
					break;
				} else if(itFirst != first->end() && (itSecond == second->end() || itFirst->getTime() < itSecond->getTime())) {
					ret->addTrace(itFirst->getTime(),VCDComparator::compareValues(itFirst->getValue(), itSecond_prev->getValue()));
					itFirst_prev = itFirst++;
				} else if(itSecond != second->end() && (itFirst == first->end() || itSecond->getTime() < itFirst->getTime())) {
					ret->addTrace(itSecond->getTime(),VCDComparator::compareValues(itSecond->getValue(), itFirst_prev->getValue()));
					itSecond_prev = itSecond++;
				} else if(itSecond->getTime() == itFirst->getTime()) {
					typename var::value_t t = VCDComparator::compareValues(itSecond->getValue(), itFirst->getValue());
					ret->addTrace(itFirst->getTime(), t);
					itSecond_prev = itSecond++;
					itFirst_prev = itFirst++;
				}
			}
			ret->setScopes(first->getScopes());
			return ret;
		}

	}
}
#endif

