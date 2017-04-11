#ifndef _FP_MEMORY_INCLUDE_
#define _FP_MEMORY_INCLUDE_
#pragma once
#include "fpHeapInterface.h"
#include "fpCommonHeap.h"
class fpMemory {
	static fpHeapInterface* CommonHeap;
public:
	static void SetCommonHeapOnce(fpHeapInterface* inHeap)
	{
		assert(CommonHeap == nullptr);
		CommonHeap = inHeap;
	}
	static void MemoryInitDefault()
	{
		SetCommonHeapOnce(new fpCommonHeap);
		CommonHeap->HeapInit();
	}
	FORCEINLINE static fpHeapInterface* GetCommonHeap()
	{
		//if (CommonHeap){return;}
		assert(CommonHeap != nullptr);
		return CommonHeap;
	}
	FORCEINLINE static fpAllocatorInterface* DefaultAllocator()
	{
		assert(CommonHeap != nullptr);
		return CommonHeap->MakeAllocator();
	}
};

#endif

