#ifndef _FP_COMMON_HEAP_INCLUDE_
#define _FP_COMMON_HEAP_INCLUDE_
#pragma once
#include "fpHeapInterface.h"
#include "../../GenericPlatform/fpPlatform.h"
class fpCommonHeap : public fpHeapInterface
{
	enum { PAGES_IN_POOL = 16 }; //FIXIT: This is test value replace on 16
	enum { START_POOL_COUNT = 2 }; //FIXIT: This is test value replace after
	struct FreeMemory
	{
		FreeMemory* next;
/* Выравнивание до 8 бит для 32 битных систем*/
#ifdef PLATFORM_32
		uint32 _allign;
#endif		
	};
	struct Pool
	{
		FreeMemory* FreeMem;
		uint32 TableIndex;
		uint32 BlockSize;
		uint32 FreeBlocks;

//выравниваем до 32 бит
#ifdef PLATFORM_64		
		uint32 align[3];	
#endif
#ifdef PLATFORM_32
        uint32 align[4];
#endif
	};
	struct PoolList 
	{
		Pool* first;
		FreeMemory* ListFreeMemPtr;
		uint32 BlockSize;
		uint32 PoolCount;
		Pool* makeNewPool(uint32 inBlockSize);
		FORCEINLINE void* getPoolRawData(Pool* pool);
		FORCEINLINE void* inPoolAllocate(Pool* inPool);
		FORCEINLINE void  inPoolDeallocate(Pool* inPool, void* inPtr);
	};
private:
	
	

public:
	void  HeapInit() override;
	void* HeapAlloc(SIZE_T size)override;
	void  HeapFree(void* target, SIZE_T size)override;
	void* HeapRealloc(void* target, SIZE_T size)override;
	void  HeapCleanup()override;
	void  HeapDestroy()override;
private:
	const uint16 POOL_SIZES[7] = {8,12,16,18,24,32,40};

};

#endif
