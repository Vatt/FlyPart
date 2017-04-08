#include "fpWindowsMemory.h"
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
/*TODO: �������� ����� ������� �������������(dwAllocationGranularity)*/
	return sys_info.dwPageSize;
}
/*FIXIT: �������� � ������, � ������� ������ ������ �� �����������*/
fpPlatformMemory::MemoryStats fpPlatformMemory::Stats = MemoryStats(GetWinTotalRam(), 1024, GetWinPageSize());

void* fpWindowsPlatformMemory::SystemAlloc(SIZE_T size)
{
    fpPlatformMemory::Stats.IncrementSystemAllocCallCounter();
	void* ptr = VirtualAlloc(NULL, size, MEM_RESERVE | MEM_COMMIT, PAGE_READWRITE);
	memset(ptr, 0, size); //FIXIT: implement function
	fpPlatformMemory::Stats.UsedMemory += size;
	return ptr;
}
void fpWindowsPlatformMemory::SystemFree(void* ptr,SIZE_T size)
{
	fpPlatformMemory::Stats.IncrementSystemFreeCallCounter();
	VirtualFree(ptr, 0, MEM_RELEASE);
	fpPlatformMemory::Stats.UsedMemory -= size;
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
	return memmove(Dest, Src, Size); //TODO: ��������, �������� �������� �� 4 8 16 32 64 �������� � ��� ��������� ��� ������
}
int32 fpWindowsPlatformMemory::MemCmp(void* const Buf1, const void* Buf2, size_t size)
{
	
	return memcmp(Buf1,Buf2, size); //TODO: ��������, �������� �������� �� 4 8 16 32 64 �������� � ��� ��������� ��� ������
}
void fpWindowsPlatformMemory::MemSwap(void* ptr1, void* ptr2, size_t size)
{
	std::swap(ptr1, ptr2); //TODO: ��������, �������� �������� �� 4 8 16 32 64 �������� � ��� ��������� ��� ������
}

void* fpWindowsPlatformMemory::MemCopy(void * dest, const void * src, SIZE_T size)
{
	return memcpy(dest, src, size);
}
