#include <cstdio>
#include <time.h>
#include <cstring>
#include <iostream>
#include "common.h"
#include "file_handling_exception.h"
#include "fst_writer.h"
#include "variable.h"
#include "libfst/fstapi.h"
#include "libfst/jrb.h"


namespace VcdCT {
	static JRB vcd_ids = NULL;
	
	void FSTWriter::writeDownFST(shared_ptr<VCDHeader>& header) {
		struct fstContext *ctx;
		fstHandle returnedhandle;
		unsigned int hash;
		ctx = (struct fstContext*)fstWriterCreate(fileName_.c_str(), 1);
		JRB node;
	  
		if(!ctx) {
			throw FileHandlingException(ERR("Cannot create output file"));
		}
		vcd_ids = make_jrb();
	  
		fstWriterSetPackType(ctx, 0);
		fstWriterSetRepackOnClose(ctx, 0); 
		fstWriterSetTimescale(ctx, header->getTimescale());
	  
		time_t rawtime;
		time(&rawtime);
	  
		fstWriterSetDate(ctx, ctime(&rawtime));
		fstWriterSetVersion(ctx, PACKAGE_STRING);
	  
	  //fstWriterSetScope(ctx, FST_ST_VCD_TASK, "skoup", NULL);
	  
		std::map< std::string,shared_ptr<ScalarVar> >& scalars = header->getScalars();
		std::map <std::string,shared_ptr<VectorVar> >& vectors = header->getVectors();
	  
		char* namebuf = new char[128];
		char* idbuf = new char[128];
		char* valbuf = new char[256];
	  //scalars
		typedef std::pair<std::string,shared_ptr<ScalarVar> > pair_s;
		foreach(pair_s p, scalars) {
		  enum fstVarType vartype;
		  VarTypeCode::VarTypeEnum varTypeCode = p.second->getVarTypeCode();
		  vartype = static_cast<enum fstVarType>(varTypeCode);
			
		  //emit $scope messages for the current variable
		  typedef std::pair<ScalarVar::ScopeType, std::string > pair1;
		  foreach(pair1 p1, p.second->getScopes()) {
			strncpy (namebuf, p1.second.c_str(), 127);				
			fstWriterSetScope(ctx, static_cast<enum fstScopeType>(p1.first), namebuf, NULL);
		  }
			
		  int len = 1;
		  strncpy (namebuf, p.second->getReference().c_str(), 127);
		  strncpy (idbuf, p.first.c_str(), 127);
		  hash = vcdid_hash(idbuf);
		  node = jrb_find_int(vcd_ids, hash);
		  //following is copy-paste from fst2vcd.c from GTKWave
		  if(!node) {
			Jval val;
			returnedhandle = fstWriterCreateVar(ctx, vartype, FST_VD_IMPLICIT, len, namebuf, 0);
			val.i = returnedhandle;
			jrb_insert_int(vcd_ids, hash, val)->val2.i = len;
		  } else {
			fstWriterCreateVar(ctx, vartype, FST_VD_IMPLICIT, node->val2.i, namebuf, node->val.i);
		  }

		  for(int i=0; i<p.second->getScopes().size(); ++i)
			fstWriterSetUpscope(ctx);	
		}
	  //vectors
	  typedef std::pair<std::string,shared_ptr<VectorVar> > pair_v;
	  foreach(pair_v p, vectors) {
			enum fstVarType vartype;
			VarTypeCode::VarTypeEnum varTypeCode = p.second->getVarTypeCode();
			vartype = static_cast<enum fstVarType>(varTypeCode);
			
			//emit $scope messages for the current variable
			typedef std::pair<VectorVar::ScopeType, std::string > pair1;
			foreach(pair1 p1, p.second->getScopes()) {
				strncpy (namebuf, p1.second.c_str(), 127);				
				fstWriterSetScope(ctx, static_cast<enum fstScopeType>(p1.first), namebuf, NULL);
			}
			
			int len = p.second->getLength();
			strncpy (namebuf, p.second->getReference().c_str(), 127);
			strncpy (idbuf, p.first.c_str(), 127);
			hash = vcdid_hash(idbuf);
			node = jrb_find_int(vcd_ids, hash);
		
		if(!node) {
			Jval val;
			returnedhandle = fstWriterCreateVar(ctx, vartype, FST_VD_IMPLICIT, len, namebuf, 0);
			val.i = returnedhandle;
			jrb_insert_int(vcd_ids, hash, val)->val2.i = len;
		} else {
			fstWriterCreateVar(ctx, vartype, FST_VD_IMPLICIT, node->val2.i, namebuf, node->val.i);
		}

		for(int i=0; i<p.second->getScopes().size(); ++i)
			fstWriterSetUpscope(ctx);	
	  }
	  // 
	  
	  std::map<std::string, ScalarVar::iterator> smap;
	  std::map<std::string, VectorVar::iterator> vmap;

	  bool sthDone = false;
	  bool timeChanged = false;
	  STime minTime(0-1, 1);
	  //value dump section
	  for(std::map< std::string,shared_ptr<ScalarVar> >::iterator it = scalars.begin(); it != scalars.end(); ++it) {
		smap[it->first] = it->second->begin();
		if(it->second->begin()->getTime() < minTime)
			minTime = it->second->begin()->getTime();
	  }
	  for(std::map< std::string,shared_ptr<VectorVar> >::iterator it = vectors.begin(); it != vectors.end(); ++it) {
		vmap[it->first] = it->second->begin();
		if(it->second->begin()->getTime() < minTime)
			minTime = it->second->begin()->getTime();
	  }
	  
	  
	  
	  STime curTime = minTime;
	  fstWriterEmitTimeChange(ctx, curTime.significand);
	  
	  for(;;) {
		sthDone = false;
		timeChanged = false;
		minTime = 0-1; //max uint64_t value
			for(std::map<std::string, ScalarVar::iterator>::iterator smapIter=smap.begin(); smapIter != smap.end(); ++smapIter) {
				if(smapIter->second != scalars[smapIter->first]->end()) {
					sthDone = true;
					if(!timeChanged) {
						fstWriterEmitTimeChange(ctx, curTime);
						timeChanged = true;
					}
					if(smapIter->second->getTime() == curTime) { 
						strncpy (idbuf, smapIter->first.c_str(), 127);
						hash = vcdid_hash(idbuf);
						node = jrb_find_int(vcd_ids, hash);
						ScalarVar::value_t val =  smapIter->second->getValue();
						valbuf[0] = val;
						valbuf[1] = '\0';
						if(node) {
							fstWriterEmitValueChange(ctx, node->val.i, valbuf);
						}
						++(smapIter->second);
					}
					if(smapIter->second != scalars[smapIter->first]->end() &&
						smapIter->second->getTime() < minTime) {
						minTime = smapIter->second->getTime();
					}
				}
			}
			
			for(std::map<std::string, VectorVar::iterator>::iterator vmapIter=vmap.begin(); vmapIter != vmap.end(); ++vmapIter) {
				if(vmapIter->second != vectors[vmapIter->first]->end()) {
					sthDone = true;
					if(!timeChanged) {
						fstWriterEmitTimeChange(ctx, curTime);
						timeChanged = true;
					}
					if(vmapIter->second->getTime() == curTime) { 
						strncpy (idbuf, vmapIter->first.c_str(), 127);
						hash = vcdid_hash(idbuf);//////////////
						node = jrb_find_int(vcd_ids, hash);
						VectorVar::value_t val =  vmapIter->second->getValue();
						int i=0;
						for(/*i=0*/; i<val.size(); ++i)
							valbuf[i] = val[i];
						valbuf[i+1] = '\0';
						if(node) {
							fstWriterEmitValueChange(ctx, node->val.i, valbuf);
						}
						++(vmapIter->second);
					}
					if(vmapIter->second != vectors[vmapIter->first]->end() &&
						vmapIter->second->getTime() < minTime) {
						minTime = vmapIter->second->getTime();
					}
				}
			}
			if(sthDone == false)
				break;
			curTime = minTime;
		}
	
		delete[] namebuf;
		delete[] idbuf;
		delete[] valbuf;
		fstWriterClose(ctx);
	}

	unsigned int FSTWriter::vcdid_hash(char *s) {
		unsigned int val = 0;
		int i, len = strlen(s);

		s+=(len-1);

		for(i=0 ; i<len ; i++) {
			val *= 94;                              /* was 94 but XL uses '!' as right hand side chars which act as leading zeros */
		  val += (((unsigned char)*s) - 32);

		  s--;
		}

		return(val);
	}  
}
