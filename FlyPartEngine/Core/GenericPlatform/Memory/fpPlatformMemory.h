#pragma once
#ifndef _FP_PLATFORM_MEMORY_
#define	_FP_PLATFORM_MEMORY_
#include "../typedefs.h"
#include "../defines.h"
struct fpPlatformMemory
{
    struct MemoryStats{
        size_t PageSize;
        size_t TotalPhysMemory;
        size_t UsedMemory;
        size_t AvailablePhysMemory;
        size_t MemoryLimit;
        MemoryStats(size_t totalPhysMem,size_t memLimit, uint32 pageSize)
            :TotalPhysMemory(totalPhysMem),MemoryLimit(memLimit),PageSize(pageSize)
        {
            AllocCallCounter=0;
            FreeCallCounter=0;
            UsedMemory=0;
        }


        size_t AllocCallCounter;
        size_t FreeCallCounter;
        void IncrementSystemAllocCallCounter(){
            AllocCallCounter++;
        }
        void IncrementSystemFreeCallCounter(){
            FreeCallCounter++;
        }

    };

    static MemoryStats Stats;
    static void* SystemAlloc(SIZE_T size);
    static void SystemFree(void* ptr,SIZE_T size);
    static void UpdateMemoryStats();
    static void* MemMove(void* Dest, const void* Src, size_t size);
    static int32 MemCmp( void* const Buf1, const void* Buf2, size_t size);
    static void  MemSwap(void* ptr1, void* ptr2, size_t size);

};

#endif
