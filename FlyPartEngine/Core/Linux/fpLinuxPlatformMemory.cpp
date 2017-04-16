#include "fpLinuxPlatformMemory.h"
#include <utility>
#include <stdlib.h>
#include <cstring>
#include <zconf.h>
#include <sys/sysinfo.h>
#include <sys/mman.h>
#include <mm_malloc.h>

fpGenericMemory::MemoryStats fpGenericMemory::Stats = MemoryStats(sysconf(_SC_PHYS_PAGES)*sysconf(_SC_PAGE_SIZE),
                    								  1024,sysconf(_SC_PAGE_SIZE));

void* fpLinuxPlatformMemory::SystemAlloc(size_t size)
{

    Stats.IncrementSystemAllocCallCounter();	
	//void* ptr =  valloc(size);
	//void* ptr = mmap(NULL,size,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,0,0);
    void* ptr = _mm_malloc(size,size);
    fpPlatformMemory::Stats.OsMemory += size;
	return ptr;
}
void fpLinuxPlatformMemory::SystemFree(void *ptr, SIZE_T size)
{
    Stats.IncrementSystemFreeCallCounter();
	//munmap(ptr, size);
    _mm_free(ptr);
	fpPlatformMemory::Stats.OsMemory -= size;
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
void* fpLinuxPlatformMemory::MemCopy(void * dest, const void * src, SIZE_T size)
{
	return memcpy(dest, src, size);
}
void* fpLinuxPlatformMemory::MemSet(void * dest, uint8 value, SIZE_T count)
{
	return memset(dest, value, count);
}