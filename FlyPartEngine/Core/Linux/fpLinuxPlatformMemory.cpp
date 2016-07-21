#include "fpLinuxPlatformMemory.h"
#include <utility>
#include <stdlib.h>
#include <cstring>

#include <malloc.h>
#include <zconf.h>
#include <sys/sysinfo.h>
//#include <linux/sysinfo.h>
fpPlatformMemory::MemoryStats fpPlatformMemory::Stats = MemoryStats(sysconf(_SC_PHYS_PAGES)*sysconf(_SC_PAGE_SIZE),
                                                                    1024,sysconf(_SC_PAGE_SIZE));

void* fpLinuxPlatformMemory::SystemAlloc(size_t size)
{

    Stats.IncrementSystemAllocCallCounter();
	return valloc(size);
}
void fpLinuxPlatformMemory::SystemFree(void* ptr)
{
    Stats.IncrementSystemFreeCallCounter();
	free(ptr);
}
void fpLinuxPlatformMemory::UpdateMemoryStats()
{
    struct sysinfo info;
    sysinfo(&info);
    Stats.AvailablePhysMemory = info.freeram;
}
void* fpLinuxPlatformMemory::MemMove(void* Dest, const void* Src, size_t Size)
{
	/*
	 * TODO: для 8 16 32 64 замениь на ручной побайтовый перенос
	 */
	return memmove(Dest, Src, Size);
}
int32 fpLinuxPlatformMemory::MemCmp(void* const Buf1, const void* Buf2, size_t size)
{
	/*
 	* TODO: для 8 16 32 64 замениь на  ручное побайтовое копирование
 	*/
	return memcmp(Buf1,Buf2, size);
}
void fpLinuxPlatformMemory::MemSwap(void* ptr1, void* ptr2, size_t size)
{
	/*
 	* TODO: для 8 16 32 64 замениь на  ручное побайтовое копирование,
	* в остальном циклично копировать
 	*/
	std::swap(ptr1, ptr2);
}
