#pragma once
#ifndef _FP_MEMORY_
#define	_FP_MEMORY_


struct MemoryStats{
	size_t usedMemory;
	size_t totalMemory;
	size_t availableMemory;
	size_t allocCallCounter;
	size_t freeCallCounter;
	size_t pageSize;
	size_t granularity;
};
class fpAllocator
{
public:
	fpAllocator(MemoryStats* stats);
	virtual ~fpAllocator();
	virtual void* allocate(size_t) = 0;
	virtual void  free(void* ptr) = 0;
protected:

	static void incAllocCallCounter(){
		fpMemorySystem::MemoryStats()->allocCallCounter++;
	}
	static void incFreeCallCounter(){
		fpMemorySystem::MemoryStats()->freeCallCounter++;
	}
};

class fpMemory
{
private:
	MemoryStats* _stats;
	fpAllocator* _allocator;
public:
	fpMemory(fpAllocator* allocator, MemoryStats* stats) :_allocator(allocator),
														  _stats(stats){}
	virtual void* SystemAlloc(size_t size) = 0;
	virtual void SystemFree(void* ptr) = 0;
	virtual fpAllocator* DefaultAllocator() = 0;

};

#endif