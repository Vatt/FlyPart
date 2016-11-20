#ifndef _FP_COMMON_HEAP_INCLUDE_
#define _FP_COMMON_HEAP_INCLUDE_
#pragma once
#include "fpHeapInterface.h"
#include "../../GenericPlatform/fpPlatform.h"
class fpCommonHeap : public fpHeapInterface
{
	enum { PAGES_IN_POOL = 1 }; //FIXIT: This is test value replace on 16
	enum { START_POOL_COUNT = 1 }; //FIXIT: This is test value replace after
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
		uint32 BlockSize;
		uint32 FreeBlocks;
#ifdef PLATFORM_64
		//выравниваем до 32 бит
		uint64 align[2];
#elif  PLATFORM_32
		//если 32 битная платформа размер равен 16 выравнивание ненужно
#endif

	};
private:
	FORCEINLINE void* getPoolRawData(Pool* pool);
	Pool* makeNewPool(uint32 inBlockSize);
	void* poolAllocate(SIZE_T size);
public:
	void  HeapInit() override;
	void* HeapAlloc(SIZE_T size)override;
	void  HeapFree(void* target, SIZE_T size)override;
	void* HeapRealloc(void* target, SIZE_T size)override;
	void  HeapCleanup()override;
	void  HeapDestroy()override;
};

#endif