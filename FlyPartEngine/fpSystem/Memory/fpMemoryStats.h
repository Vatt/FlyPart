#pragma once
#ifndef _FP_MEMORY_STATS_
#define _FP_MEMORY_STATS_
#include <stddef.h>
/* all in bytes*/
struct fpMemoryStats{
    static size_t usedMemory;
//  static size_t availableVirtualMemory;
    static size_t availablePhysMemory;

    static void SetupSats(size_t totalPhysMem,size_t memLimit, size_t  pSize, size_t granularity)
    {
        if (isInit)
        {
                //TODO: запилить ошибку. запись в лог , ибо нефиг переустанавливать
          return;
        }
        totalPhysMemory = totalPhysMem;
        pageSize = pSize;
        fpMemoryStats::granularity = granularity;
        usedMemory = 0;
//	availableVirtualMemory = totalPhysMem;
	allocCallCounter = 0;
	freeCallCounter = 0;
	isInit = true;
    }
    static void IncAllocCallCounter(){
        allocCallCounter++;
    }
    static void IncFreeCallCounter(){
        freeCallCounter++;
    }
    static void SetNewMemLimit(size_t newMemLimit)
    {
       memoryLimit = newMemLimit;
    }
	/*in bytes*/
    static size_t PageSize()       { return pageSize;    }
	/*in bytes*/
    static size_t Granularity()    { return granularity; }
	/*in bytes*/
	static size_t TotalPhysMemory(){ return totalPhysMemory; }
    static size_t MemoryLimit()    { return memoryLimit; }
private:
	static size_t pageSize;
	static size_t granularity;
	static size_t totalPhysMemory;

	static size_t memoryLimit;
	static size_t allocCallCounter;
	static size_t freeCallCounter;
	static bool isInit;
};
#endif
