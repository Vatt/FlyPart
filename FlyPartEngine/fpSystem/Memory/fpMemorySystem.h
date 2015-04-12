
#pragma once
#ifndef _FP_MEMORY_SYSTEM
#	define _FP_MEMORY_SYSTEM
#include "fpMemory.h"

struct MemoryConstants
{

};
class fpMemorySystem
{
private:
	static MemoryStats* _stats;
	static fpMemory* _globalMem;
public:
	static void			Init(fpMemory* memory) { _globalMem = memory; }
	static MemoryStats* MemoryStats()          { return _stats;    }
	static fpMemory*    GlobalMemory()		   { return _globalMem; }
};



#endif