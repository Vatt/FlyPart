#include "fpWindowsMemory.h"



fpWindowsMemory::fpWindowsMemory() :fpPlatformMemory(nullptr)
{
	SYSTEM_INFO sys_info;
	MEMORYSTATUSEX mem_info;
	GetSystemInfo(&sys_info);
	mem_info.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&mem_info);
	fpMemoryStats::SetupSats(mem_info.ullTotalPhys,1024, sys_info.dwPageSize, sys_info.dwAllocationGranularity);
	
}
void* fpWindowsMemory::SystemAlloc(size_t size)
{
    fpMemoryStats::IncAllocCallCounter();
	return VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
}
void fpWindowsMemory::SystemFree(void* ptr)
{
    fpMemoryStats::IncFreeCallCounter();
	VirtualFree(ptr,0, MEM_RELEASE );
}
void fpWindowsMemory::UpdateMemoryStats()
{
	MEMORYSTATUSEX mem_info;
	mem_info.dwLength = sizeof(MEMORYSTATUSEX);
	GlobalMemoryStatusEx(&mem_info);
	fpMemoryStats::availablePhysMemory = mem_info.ullAvailPhys;
}
