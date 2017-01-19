
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
	~fpAllocator() 
	{

	};
	virtual void* allocate(size_t size) = 0;
	virtual void  free(void* ptr) = 0;
};
class fpFixedAllocator:public fpAllocatorInterface{
	uint32 _size;
public:
	fpFixedAllocator(fpHeapInterface* heap,uint32 block_size) : fpAllocatorInterface(heap),_size(block_size)
	{}
	virtual void* allocate(size_t size);
	virtual void  free(void* ptr);

};
#endif
