#ifndef _FP_COMMON_HEAP_INCLUDE_
#define _FP_COMMON_HEAP_INCLUDE_
#pragma once
#include "fpHeapInterface.h"
#include "../../GenericPlatform/fpPlatform.h"
class fpCommonHeap : public fpHeapInterface
{
	enum { PAGES_IN_POOL = 16 }; //FIXIT: This is test value replace on 16
	enum { START_POOL_COUNT = 2 }; //FIXIT: This is test value replace after
    enum { NUMBER_OF_POOL_PER_ONE_EXTEND = 2 };
	struct FreeMemory
	{
		FreeMemory* next;
/* Выравнивание до 8 бит на 32 битной платформе*/
#ifdef PLATFORM_32
		uint32 _allign;
#endif		
	};
	struct PoolHeader
	{
		FreeMemory* FreeMem;
		PoolHeader* Next;
		uint32 BlockSize;
		uint32 FreeBlocks;

//выравнивание до 32 бит
#ifdef PLATFORM_64		
		uint32 _padding_[2];
#endif
/*
#ifdef PLATFORM_32
        uint32 align[4];
#endif
*/
	};

	struct PoolList 
	{
		/*
		* Global pointer of free memory blocks in this list
		*/
		FreeMemory* ListFreeMemory;
        PoolHeader*  Front;
        uint32 TableIndex;
		uint32 BlockSize;
		uint32 PoolCount;
        uint32 BlocksNumPerPool;
		uint32 ListFreeBlocksCount;
        PoolList(uint32 block_size);
		PoolHeader* makeNewPool()const;
        /*
         * This method only for validate list;
         * */
        FORCEINLINE uint32 CalcRealNumFreeBlocks()const;
        FORCEINLINE void  LinkPoolToFront(PoolHeader* target);
		FORCEINLINE void* GetPoolRawData(PoolHeader *pool)const;
		FORCEINLINE void* PoolAllocate();
		FORCEINLINE void  PoolFree(void *inPtr);
        FORCEINLINE void  ExtendPoolsCount(uint32 num);
    };
    struct PoolTable
    {

    };
private:
	
	

public:
	void  HeapInit() override;
	void* HeapAlloc(SIZE_T size)override;
	void  HeapFree(void* target, SIZE_T size)override;
	void* HeapRealloc(void* target, SIZE_T size)override;
	void  HeapCleanup()override;
	void  HeapDestroy()override;

	virtual ~fpCommonHeap();
private:
	const uint16 POOL_SIZES[7] = {8,12,16,18,24,32,40};
    PoolTable table;

};

#endif
