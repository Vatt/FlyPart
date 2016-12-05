#include "fpCommonHeap.h"
#include <new>

void fpCommonHeap::HeapInit()
{
	for (uint32 index = 0; index <= START_POOL_COUNT;index++)
	{
        makeNewPool(POOL_SIZES[index]);
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


	FreeMemory* ptr = (FreeMemory*)getPoolRawData(pool);
	pool->FreeMem = ptr;
	UINTPTR mem_pos = (UINTPTR)((UINTPTR)getPoolRawData(pool) + inBlockSize);
	UINTPTR end_mem_pos = mem_pos  + (blocks_count * inBlockSize);
	FreeMemory& free_mem = *ptr;
	while (mem_pos < end_mem_pos)
	{
		free_mem.next = new((void*)mem_pos)FreeMemory;
		free_mem = *free_mem.next;
		mem_pos += inBlockSize;

	}

	return pool;
}
FORCEINLINE void* fpCommonHeap::inPoolAllocate(Pool* inPool)
{
	if (inPool->FreeBlocks == 0)
	{
		inPool->FreeMem = nullptr;
		return nullptr;
	}

    FreeMemory* new_free_mem = inPool->FreeMem->next;
    void* allocated = inPool->FreeMem;
    inPool->FreeMem = new_free_mem;
    inPool->FreeBlocks -= 1;
    return allocated;
}
FORCEINLINE void  fpCommonHeap::inPoolDeallocate(Pool* inPool, void* inPtr)
{
    FreeMemory* new_free_mem = new(inPtr)FreeMemory;
    new_free_mem->next = inPool->FreeMem;
    inPool->FreeMem  = new_free_mem;
    inPool->FreeBlocks += 1;

}
