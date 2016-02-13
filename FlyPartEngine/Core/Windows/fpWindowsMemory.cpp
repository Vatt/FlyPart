#include "fpWindowsMemory.h"
#include "../GenericPlatform/Memory/fpMemorySystem.h"
#include "../CoreAbstractLayer/fpMemoryStats.h"
#include <wchar.h>
#include <utility>
#include <Windows.h>
fpPlatformMemory* fpMemorySystem::platformMemory = new fpWindowsMemory();
fpWindowsMemory::fpWindowsMemory() :fpPlatformMemory()
{
	SYSTEM_INFO sys_info;
	MEMORYSTATUSEX mem_info;
	GetSystemInfo(&sys_info);
	mem_info.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&mem_info);
	fpMemoryStats::SetupSats(mem_info.ullTotalPhys,1024, sys_info.dwPageSize, sys_info.dwAllocationGranularity);
    //TODO: выше строка с заглушкой
}
void* fpWindowsMemory::SystemAlloc(size_t size)
{
    fpMemoryStats::IncrementSystemAllocCallCounter();
	return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}
void fpWindowsMemory::SystemFree(void* ptr)
{
    fpMemoryStats::IncrementSystemFreeCallCounter();
	VirtualFree(ptr,0, MEM_RELEASE );
}
void fpWindowsMemory::UpdateMemoryStats()
{
	MEMORYSTATUSEX mem_info;
	mem_info.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&mem_info);
	fpMemoryStats::availablePhysMemory = mem_info.ullAvailPhys;
}
void* fpWindowsMemory::MemMove(void* Dest, const void* Src, size_t Size)
{
	return memmove(Dest, Src, Size); //TODO: Заглушка, свапилку запилить на 4 8 16 32 64 варианты и все остальное как дефолт
}
int32 fpWindowsMemory::MemCmp(void* const Buf1, const void* Buf2, size_t size)
{
	
	return memcmp(Buf1,Buf2, size); //TODO: Заглушка, свапилку запилить на 4 8 16 32 64 варианты и все остальное как дефолт
}
void fpWindowsMemory::MemSwap(void* ptr1, void* ptr2, size_t size)
{
	std::swap(ptr1, ptr2); //TODO: Заглушка, свапилку запилить на 4 8 16 32 64 варианты и все остальное как дефолт
}
