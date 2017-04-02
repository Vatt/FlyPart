#pragma once
#ifndef _FP_PLATFORM_MEMORY_
#define	_FP_PLATFORM_MEMORY_
#include "../typedefs.h"
#include "../defines.h"
struct fpPlatformMemory
{
    struct MemoryStats{
        SIZE_T PageSize;
        SIZE_T TotalPhysMemory;
        SIZE_T UsedMemory;
        SIZE_T AvailablePhysMemory;
        SIZE_T MemoryLimit;
        MemoryStats(SIZE_T totalPhysMem,SIZE_T memLimit, uint32 pageSize)
            :TotalPhysMemory(totalPhysMem),MemoryLimit(memLimit),PageSize(pageSize)
        {
            AllocCallCounter=0;
            FreeCallCounter=0;
            UsedMemory=0;
        }


        SIZE_T AllocCallCounter;
        SIZE_T FreeCallCounter;
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
    static void* MemMove(void* Dest, const void* Src, SIZE_T size);
    static int32 MemCmp( void* const Buf1, const void* Buf2, SIZE_T size);
    static void  MemSwap(void* ptr1, void* ptr2, SIZE_T size);

};

#endif
