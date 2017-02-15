#ifndef _FP_COMMON_HEAP_INCLUDE_
#define _FP_COMMON_HEAP_INCLUDE_
#pragma once
#include "fpHeapInterface.h"
#include "../../GenericPlatform/fpPlatform.h"
class fpCommonHeap : public fpHeapInterface
{
	enum { PAGES_IN_POOL = 16 };
	enum { START_POOL_COUNT = 1 }; //FIXIT: This is test value replace after
	struct FreeMemory
	{
		FreeMemory* next;
/* Выравнивание до 8 байт на 32 битной платформе*/
#ifdef PLATFORM_32
		uint32 _allign;
#endif		
	};
	struct PoolHeader
	{
		FreeMemory* FreeMem;
		PoolHeader* Next;
/* Выравнивание до 16 байт на 32  битной платформе*/
#ifdef PLATFORM_32
        uint32 align[2];
#endif

	};

	struct PoolList 
	{

        struct ListHashNode{
            UINTPTR PoolKey;
            PoolHeader* PoolPtr;
        };
      //  ListHashNode* HashTable[];
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

        uint32 Lenght;
        uint32 RealHashTableSize;
		PoolList() {};
        PoolList(uint32 block_size, uint32 table_index);
		PoolHeader* makeNewPool();
		FORCEINLINE SIZE_T PoolSizeCalc();
		FORCEINLINE SIZE_T PoolDataSizeCalc();
		FORCEINLINE void  MapThePoolOfFreeBlocks(PoolHeader* pool);
        FORCEINLINE void  LinkPoolToFront(PoolHeader* target);
		FORCEINLINE void* GetPoolRawData(PoolHeader *pool)const;
		FORCEINLINE void* PoolAllocate();
		FORCEINLINE void  PoolFree(void *inPtr);
        FORCEINLINE void  ExtendPoolsCount(uint32 num);		
		FORCEINLINE void  CleanupList();
		FORCEINLINE void  CleanupPool(PoolHeader* pool);
		FORCEINLINE void  ListDestroy();
		FORCEINLINE void  PoolDestroy(PoolHeader* pool);
        /*
         * This method only for validate list;
         * */
        FORCEINLINE uint32 CalcRealNumFreeBlocks()const;
        /*
         * This method only for validate list;
         * */        
        FORCEINLINE bool  ValidateList()const;
        

    };

	class CommonAllocator:public fpAllocatorInterface
	{
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
	
	PoolList* PoolTable[9];

};

#endif
