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
	uint32 size_alloc = fpMemory::Stats.PageSize * PAGES_IN_POOL;
	uint32 pool_size = size_alloc - sizeof(Pool);
	uint32 blocks_count = pool_size / inBlockSize;
	void* memory = fpMemory::SystemAlloc(size_alloc);

	/*первые 32 байта информация о самом пуле*/
	pool = new(memory)Pool();
	pool->BlockSize = inBlockSize;
	pool->FreeBlocks = blocks_count;
	FreeMemory* first = new((uint8*)getPoolRawData(pool))FreeMemory;
	for (uint32  mem_ind = 1; mem_ind <= blocks_count; mem_ind++)
	{
		FreeMemory* newMem = new((FreeMemory*)(first + mem_ind))FreeMemory;
		FreeMemory* prevMem = ((FreeMemory*)newMem - 1);
		prevMem->next = newMem;
	}
	pool->FreeMem = first;
	return pool;
}
void* fpCommonHeap::poolAllocate(SIZE_T size)
{
	//assert(size)
	return nullptr;
}