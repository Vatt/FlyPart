#ifndef _FP_COMMON_HEAP_INCLUDE_
#define _FP_COMMON_HEAP_INCLUDE_
#pragma once
#include "fpHeapInterface.h"
#include "../../GenericPlatform/fpPlatform.h"
class fpCommonHeap : public fpHeapInterface
{
	enum { PAGES_IN_POOL = 16,
		   START_POOL_COUNT = 3, //FIXIT: This is test value replace after
		   EXTEND_NUMBER = 3,
		   
	}; 
	struct FreeMemory;
	struct PoolHeader;
	class PoolList;

	class CommonAllocator:public fpAllocatorInterface
	{
		struct ListHashBucket;
		enum {
				NO_INIT_TABLE_INDEX = -1,
				PERFECT_ALLOC_FREE_FAIL = -2
		};
        int16 	TableIndex;
	public:
		CommonAllocator(fpCommonHeap* heap);
		FORCEINLINE virtual void* Allocate(SIZE_T size)override;
		FORCEINLINE virtual void Free(void *ptr, SIZE_T size)override;
		FORCEINLINE virtual void* Realloc(void* ptr, SIZE_T size)override;
		virtual ~CommonAllocator();
	};

public:

	virtual void  HeapInit() override;
	virtual void* HeapAlloc(SIZE_T size)override;
	virtual void  HeapFree(void* target, SIZE_T size)override;
	virtual void* HeapRealloc(void* target, SIZE_T size)override;
	virtual void  HeapCleanup()override;
	
	virtual void  HeapDestroy()override;
	virtual bool  ValidateHeap()override;
	
	virtual fpAllocatorInterface* MakeDefaultAllocator();
	fpCommonHeap();
	virtual ~fpCommonHeap();
private:
    fpCommonHeap(const fpCommonHeap&);
    fpCommonHeap(fpCommonHeap&&);
    fpCommonHeap& operator=(const fpCommonHeap&);
    fpCommonHeap& operator=(fpCommonHeap&&);
private:
	uint32 MaxHashBuckets;
	PoolList* PoolTable[9];

};

#endif
