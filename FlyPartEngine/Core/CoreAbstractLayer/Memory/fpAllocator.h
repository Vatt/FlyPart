
#ifndef _FP_ALLOCATOR_
#define _FP_ALLOCATOR_
#include "../../GenericPlatform/fpPlatform.h"
#include "fpHeapInterface.h"
class fpMemorySystem;
class fpAllocatorInterface
{
	fpHeapInterface* Heap;
public:
	fpAllocatorInterface(fpHeapInterface* heap) :Heap(heap)
	{}
	virtual void* Allocate(SIZE_T size) = 0;
	virtual void  Free(void* ptr) = 0;
	virtual void* Realloc(void* ptr, SIZE_T size) = 0;
	virtual ~fpAllocatorInterface()=0;
};
#endif
