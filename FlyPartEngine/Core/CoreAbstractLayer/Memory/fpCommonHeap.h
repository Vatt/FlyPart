#ifndef _FP_COMMON_HEAP_INCLUDE_
#define _FP_COMMON_HEAP_INCLUDE_
#pragma once
#include "fpHeapInterface.h"
#include "../../GenericPlatform/fpPlatform.h"
class fpCommonHeap : public fpHeapInterface
{
	enum { PAGES_IN_POOL = 1 }; //FIXIT: This is test value replace on 16
	enum { START_POOL_COUNT = 4 }; //FIXIT: This is test value replace after
	struct FreeMemory
	{
		FreeMemory* next;
/* ������������ �� 8 ��� ��� 32 ������ ������*/
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
//����������� �� 32 ���
#ifdef PLATFORM_64		
		uint32 align[3];	
#endif
#ifdef PLATFORM_32
        uint32 align[4];
#endif
	};
private:
	FORCEINLINE void* getPoolRawData(Pool* pool);
	Pool* makeNewPool(uint32 inBlockSize);
    FORCEINLINE void* inPoolAllocate(Pool* inPool);
    FORCEINLINE void  inPoolDeallocate(Pool* inPool, void* inPtr);
public:
	void  HeapInit() override;
	void* HeapAlloc(SIZE_T size)override;
	void  HeapFree(void* target, SIZE_T size)override;
	void* HeapRealloc(void* target, SIZE_T size)override;
	void  HeapCleanup()override;
	void  HeapDestroy()override;
private:
	const uint16 POOL_SIZES[4] = {8,16,32,40};
	//Pool** PoolTable;
};

#endif
