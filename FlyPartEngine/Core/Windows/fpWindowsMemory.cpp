#include "fpWindowsMemory.h"
#include "../GenericPlatform/Memory/fpMemorySystem.h"
#include <wchar.h>
#include <utility>
#include <Windows.h>
FORCEINLINE DWORDLONG GetWinTotalRam() {
//	SYSTEM_INFO sys_info;
    MEMORYSTATUSEX mem_info;
	mem_info.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&mem_info);
	return mem_info.ullTotalPhys;
}
FORCEINLINE DWORDLONG GetWinPageSize() {
	SYSTEM_INFO sys_info;
//	MEMORYSTATUSEX mem_info;
	GetSystemInfo(&sys_info);
/*TODO: возможно лучше указать гранулярность(dwAllocationGranularity)*/
	return sys_info.dwPageSize;
}
/*FIXIT: Заглушка в лимите, с лимитом вообще ничего не проверяется*/
fpPlatformMemory::MemoryStats fpPlatformMemory::Stats = MemoryStats(GetWinTotalRam(), 1024, GetWinPageSize());

void* fpWindowsPlatformMemory::SystemAlloc(SIZE_T size)
{
    fpPlatformMemory::Stats.IncrementSystemAllocCallCounter();
	void* ptr = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	memset(ptr, 0, size); //FIXIT: implement function
	return ptr;
}
void fpWindowsPlatformMemory::SystemFree(void* ptr)
{
	fpPlatformMemory::Stats.IncrementSystemFreeCallCounter();
	VirtualFree(ptr,0, MEM_RELEASE );
}
void fpWindowsPlatformMemory::UpdateMemoryStats()
{
	MEMORYSTATUSEX mem_info;
	mem_info.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&mem_info);
	fpPlatformMemory::Stats.AvailablePhysMemory = mem_info.ullAvailPhys;
}
void* fpWindowsPlatformMemory::MemMove(void* Dest, const void* Src, size_t Size)
{
	return memmove(Dest, Src, Size); //TODO: Заглушка, свапилку запилить на 4 8 16 32 64 варианты и все остальное как дефолт
}
int32 fpWindowsPlatformMemory::MemCmp(void* const Buf1, const void* Buf2, size_t size)
{
	
	return memcmp(Buf1,Buf2, size); //TODO: Заглушка, свапилку запилить на 4 8 16 32 64 варианты и все остальное как дефолт
}
void fpWindowsPlatformMemory::MemSwap(void* ptr1, void* ptr2, size_t size)
{
	std::swap(ptr1, ptr2); //TODO: Заглушка, свапилку запилить на 4 8 16 32 64 варианты и все остальное как дефолт
}
