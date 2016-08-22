#ifndef _FP_HEAP_INLUDE_
#define _FP_HEAP_INCLUDE_
#pragma once
#include "../../GenericPlatform/fpPlatform.h"
struct fpHeapInterface
{
	virtual void  HeapInit() = 0;
	virtual void* HeapAlloc(SIZE_T size) = 0;
	virtual void  HeapFree(void* target, SIZE_T size) = 0;
	virtual void* HeapRealloc(void* target, SIZE_T size) = 0;
	virtual void  HeapCleanup() = 0;
	virtual void  HeapDestroy() = 0;
};

#endif
