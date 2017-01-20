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
//		uint32 FreeBlocks;

//выравнивание до 32 бит
#ifdef PLATFORM_64		
		uint32 _padding_[3];
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
        FORCEINLINE void  LinkPoolToFront(PoolHeader* target);
		FORCEINLINE void* GetPoolRawData(PoolHeader *pool)const;
		FORCEINLINE void* PoolAllocate();
		FORCEINLINE void  PoolFree(void *inPtr);
        FORCEINLINE void  ExtendPoolsCount(uint32 num);		
        /*
         * This method only for validate list;
         * */
        FORCEINLINE uint32 CalcRealNumFreeBlocks()const;
        /*
         * This method only for validate list;
         * */        
        FORCEINLINE uint32 CalcNumFreeBlocks()const;
        /*
         * This method only for validate list;
         * */        
        FORCEINLINE bool  ValidateList()const;
        

    };

	class CommonAllocator:public fpAllocatorInterface
	{
		uint16 	TableIndex;
	public:
		CommonAllocator(fpCommonHeap* heap);
		virtual void* Allocate(SIZE_T size);
		virtual void  Free(void* ptr);
		virtual void* Realloc(void* ptr, SIZE_T size);	
		virtual ~CommonAllocator();
	};

public:
	/*
	virtual void  HeapInit() override;
	virtual void* HeapAlloc(SIZE_T size)override;
	virtual void  HeapFree(void* target, SIZE_T size)override;
	virtual void* HeapRealloc(void* target, SIZE_T size)override;
	virtual void  HeapCleanup()override;
	*/
	virtual void  HeapDestroy()override;
	virtual bool  ValidateHeap()override;
	
	virtual fpAllocatorInterface* MakeAllocator();

	virtual ~fpCommonHeap();
private:
	const uint32 POOL_SIZES[9] = {8,12,16,18,24,32,40,48,64};
    const PoolList* PoolTable[9] = {
    	new PoolList(POOL_SIZES[0]),
    	new PoolList(POOL_SIZES[1]),
    	new PoolList(POOL_SIZES[2]),
    	new PoolList(POOL_SIZES[3]),
    	new PoolList(POOL_SIZES[4]),
    	new PoolList(POOL_SIZES[5]),
    	new PoolList(POOL_SIZES[6]),
    	new PoolList(POOL_SIZES[7]),
    	new PoolList(POOL_SIZES[8])
    };

};

#endif
