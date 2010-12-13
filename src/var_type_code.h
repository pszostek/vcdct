#ifndef __VARTYPECODE_H
#define __VARTYPECODE_H

struct VarTypeCode
{
	enum VarTypeEnum {  event = 0, integer, parameter, real, realparameter, reg, supply0, supply1, time, tri, triand, trior, trireg, tri0, tri1, wand, wire, wor};
};
typedef struct VarTypeCode VarTypeCode;
#endif //VARTYPECODE

