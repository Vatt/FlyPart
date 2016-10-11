
#ifndef _FP_ALLOCATOR_
#define _FP_ALLOCATOR_
#include "../../GenericPlatform/fpPlatform.h"
#include "fpHeapInterface.h"
class fpMemorySystem;
class fpAllocator
{
	fpHeapInterface* _heap;
public:
	fpAllocator(fpHeapInterface* heap) :_heap(heap)
	{}
	~fpAllocator() 
	{
		_heap->HeapCleanup();
		_heap->HeapDestroy();
	};
	virtual void* allocate(size_t size) = 0;
	virtual void  free(void* ptr) = 0;
	
};

#endif
