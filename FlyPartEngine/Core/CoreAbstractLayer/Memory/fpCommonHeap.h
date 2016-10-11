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
	};
	struct Pool
	{
//		void* RawData;
		FreeMemory* FreeMem;
		uint32 BlockSize;
		uint32 FreeBlocks;
#ifdef PLATFORM_64
		//выравниваем до 32 бит
		uint64 align;
#elif  PLATFORM_32
		//если 32 битная платформа размер равен 16 выравнивание ненужно
#endif

	};
private:
	FORCEINLINE void* getPoolRawData(Pool* pool);
	Pool* makeNewPool(uint32 inBlockSize);
public:
	void  HeapInit();
	void* HeapAlloc(SIZE_T size);
	void  HeapFree(void* target, SIZE_T size);
	void* HeapRealloc(void* target, SIZE_T size);
	void  HeapCleanup();
	void  HeapDestroy();
};

#endif