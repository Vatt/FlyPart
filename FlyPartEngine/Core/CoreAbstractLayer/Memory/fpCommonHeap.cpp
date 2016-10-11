#include "fpCommonHeap.h"
#include <new>

void fpCommonHeap::HeapInit()
{
	for (uint32 index = 0; index <= START_POOL_COUNT;index++)
	{
		makeNewPool(16);
	}
}

void * fpCommonHeap::HeapAlloc(SIZE_T size)
{
	return nullptr;
}

void fpCommonHeap::HeapFree(void * target, SIZE_T size)
{
}

void fpCommonHeap::HeapCleanup()
{
	
}

void fpCommonHeap::HeapDestroy()
{
}

void * fpCommonHeap::HeapRealloc(void * target, SIZE_T size)
{
	return nullptr;
}

void * fpCommonHeap::getPoolRawData(Pool * pool)
{
	return (pool + sizeof(Pool));
}

fpCommonHeap::Pool* fpCommonHeap::makeNewPool(uint32 inBlockSize)
{
	Pool* pool;
	uint8* RawData;
	SIZE_T first_mem_pos;
	SIZE_T end_mem_pos;
	SIZE_T offset;
	uint32 size_alloc = fpMemory::Stats.PageSize * PAGES_IN_POOL;
	uint32 pool_size = size_alloc - sizeof(Pool);
	uint32 blocks_count = pool_size / inBlockSize;
	void* memory = fpMemory::SystemAlloc(size_alloc);

	/*первые 32 байта информация о самом пуле*/
	pool = new(memory)Pool();
	pool->BlockSize = inBlockSize;
	RawData = (uint8*)getPoolRawData(pool);	//(void*)((uint8)memory + sizeof(Pool));
	first_mem_pos = (SIZE_T)RawData;
	end_mem_pos = first_mem_pos + pool_size;
	pool->FreeBlocks = blocks_count;
	/*
		добавить потом указатель на FreeMem
	*/
	FreeMemory* first = new(RawData)FreeMemory();
	offset = inBlockSize;
	for (; offset <= pool_size; offset += inBlockSize)
	{
		FreeMemory* newMem = new((void*)(first_mem_pos+offset))FreeMemory;
		FreeMemory* prevMem = (FreeMemory*)(first_mem_pos + (offset - inBlockSize));
		prevMem->next = newMem;
	}
	return pool;
}
