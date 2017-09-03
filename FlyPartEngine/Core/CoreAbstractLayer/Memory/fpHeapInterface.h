#ifndef _FP_HEAP_INCLUDE_
#define _FP_HEAP_INCLUDE_
#pragma once
#include "../../GenericPlatform/fpPlatform.h"
#include "fpAllocator.h"

class fpHeapInterface
{
public:
	virtual void  HeapInit() = 0;
	
	virtual void* HeapAlloc(SIZE_T size) = 0;
	virtual void  HeapFree(void* target, SIZE_T size) = 0;
	virtual void* HeapRealloc(void* target, SIZE_T size) = 0;
	virtual void  HeapCleanup() = 0;
	
	virtual void  HeapDestroy() = 0;
	virtual bool  ValidateHeap() =0;
	virtual fpAllocatorInterface* MakeAllocator()=0;
};

#endif
