#include "fpLinuxMemory.h"
#include "../GenericPlatform/Memory/fpMemorySystem.h"
#include "../CoreAbstractLayer/fpMemoryStats.h"

#include <utility>
#include <stdlib.h>
#include <cstring>
#include <zconf.h>
#include <linux/sysinfo.h>


fpPlatformMemory* fpMemorySystem::platformMemory = new fpLinuxMemory();
fpLinuxMemory::fpLinuxMemory() :fpPlatformMemory()
{
	fpMemoryStats::SetupSats(sysinfo().totalram,1024, sysconf(_SC_PAGE_SIZE),0);
    //TODO: убрать заглушку
}
void* fpLinuxMemory::SystemAlloc(size_t size)
{
    fpMemoryStats::IncrementSystemAllocCallCounter();
	return valloc(size);
}
void fpLinuxMemory::SystemFree(void* ptr)
{
    fpMemoryStats::IncrementSystemFreeCallCounter();
	free(ptr);
}
void fpLinuxMemory::UpdateMemoryStats()
{
	fpMemoryStats::availablePhysMemory = sysinfo().freeram;
}
void* fpLinuxMemory::MemMove(void* Dest, const void* Src, size_t Size)
{
	/*
	 * TODO: для 8 16 32 64 замениь на ручной побайтовый перенос
	 */
	return memmove(Dest, Src, Size);
}
int32 fpLinuxMemory::MemCmp(void* const Buf1, const void* Buf2, size_t size)
{
	/*
 	* TODO: для 8 16 32 64 замениь на  ручное побайтовое копирование
 	*/
	return memcmp(Buf1,Buf2, size);
}
void fpLinuxMemory::MemSwap(void* ptr1, void* ptr2, size_t size)
{
	/*
 	* TODO: для 8 16 32 64 замениь на  ручное побайтовое копирование,
	* в остальном циклично копировать
 	*/
	std::swap(ptr1, ptr2);
}
