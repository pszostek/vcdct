#include <list>
#include <string>
#include <iostream>
#include <utility>
#include <iostream>
#include "common.h"
#include "var_type_code.h"
#include "trace.h"
#include "vcd_comparator.h"
#include "vcd_comparator.hpp"

namespace VcdCT {

	shared_ptr<VCDHeader> VCDComparator::compareFiles(shared_ptr<VCDHeader> h1, shared_ptr<VCDHeader> h2) {
		shared_ptr<VCDHeader> ret = shared_ptr<VCDHeader>(new VCDHeader());
		
		{ /* scope for vectors */
		    std::map<std::string, shared_ptr<VectorVar> >::const_iterator h1VecIter= h1->getVectors().begin();
		    std::map<std::string, shared_ptr<VectorVar> >::const_iterator h2VecIter= h2->getVectors().begin();
		
		    const std::map<std::string, shared_ptr<VectorVar> >::const_iterator h1VecEnd= h1->getVectors().end();
		    const std::map<std::string, shared_ptr<VectorVar> >::const_iterator h2VecEnd= h2->getVectors().end();
		    while(h1VecIter != h1VecEnd && h2VecIter != h2VecEnd) {
			    if(h1VecIter->first == h2VecIter->first &&  /* if names, types, lengths and scopes are equal then issue a comparison */
				    h1VecIter->second->getVarTypeCode() == h2VecIter->second->getVarTypeCode() &&
				    h1VecIter->second->getLength() == h2VecIter->second->getLength() &&
				    h1VecIter->second->getScopes() == h2VecIter->second->getScopes() ) {
				    
					VarTypeCode::VarTypeEnum newType = h1VecIter->second->getVarTypeCode();
					std::string newIdentifier = h1VecIter->second->getIdentifier() + h2VecIter->second->getIdentifier() ;
					std::string newReference = h1VecIter->second->getReference() + "_comp";
					unsigned newLength = h1VecIter->second->getLength();
				
			      	shared_ptr<VectorVar> newVector = shared_ptr<VectorVar>(new VectorVar(newType, newIdentifier, newReference, newLength));
			      	compareVariables<VectorVar>(h1VecIter->second, h2VecIter->second, newVector);
			      	ret->addVector(newVector);
				    ++h1VecIter;
				    ++h2VecIter;
			    } else if(h1VecIter->first < h2VecIter->first) {
				    ++h1VecIter;
			    } else { //h2VecIter->first < h1VecIter->first)
				    ++h2VecIter;
			    }
		    }
		}
		{   /*scope for scalars */
		    std::map<std::string, shared_ptr<ScalarVar> >::const_iterator h1ScalarIter= h1->getScalars().begin();
		    std::map<std::string, shared_ptr<ScalarVar> >::const_iterator h2ScalarIter= h2->getScalars().begin();
		
		    const std::map<std::string, shared_ptr<ScalarVar> >::const_iterator h1ScalarEnd= h1->getScalars().end();
		    const std::map<std::string, shared_ptr<ScalarVar> >::const_iterator h2ScalarEnd= h2->getScalars().end();	
		    while(h1ScalarIter != h1ScalarEnd && h2ScalarIter != h2ScalarEnd) {
			    if(h1ScalarIter->first == h2ScalarIter->first &&
				    h1ScalarIter->second->getVarTypeCode() == h2ScalarIter->second->getVarTypeCode() &&
				    h1ScalarIter->second->getScopes() == h2ScalarIter->second->getScopes() ) {
				    
					VarTypeCode::VarTypeEnum newType = h1ScalarIter->second->getVarTypeCode();
					std::string newIdentifier = h1ScalarIter->second->getIdentifier() + h2ScalarIter->second->getIdentifier() ;
					std::string newReference = h1ScalarIter->second->getReference() + "_comp";
					
				    shared_ptr<ScalarVar> newScalar = shared_ptr<ScalarVar>(new ScalarVar(newType, newIdentifier, newReference));
				    compareVariables<ScalarVar>(h1ScalarIter->second, h2ScalarIter->second, newScalar);
				    ret->addScalar(newScalar);
				   // DBG_MSG("issued comparison of scalar " + h1ScalarIter->first);
				    ++h1ScalarIter;
				    ++h2ScalarIter;
			    } else if(h1ScalarIter->first < h2ScalarIter->first) {
				    ++h1ScalarIter;
			    } else { //h2ScalarIter->first < h1ScalarIter->first)
				    ++h2ScalarIter;
			    }
		    }
		}
		return ret;
	}
} //namespace

