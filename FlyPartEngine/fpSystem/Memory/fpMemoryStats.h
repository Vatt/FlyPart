#pragma once
#ifndef _FP_MEMORY_STATS_
#define _FP_MEMORY_STATS_
/* all in bytes*/
struct fpMemoryStats{
	static size_t usedMemory;
	static size_t availableVirtualMemory;
	static size_t availablePhysMemory;

	static void SetupSats(size_t totalPhysMem,size_t totalVirtualMem, size_t  pSize, size_t granularity)
	{
		if (isInit)
		{
			//TODO: �������� ������. ������ � ��� , ��� ����� �����������������
			return;
		}
		totalPhysMemory = totalPhysMem;
		pageSize = pSize;
		granularity = granularity;
		usedMemory = 0;
		availableVirtualMemory = totalPhysMem;
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
	static void SetNewTotalVirtualMemSize(size_t newTotalVirtualMemSyze)
	{
		totalVirtualMemory = newTotalVirtualMemSyze;
	}
	/*in bytes*/
	static size_t PageSize()   { return pageSize;    }
	/*in bytes*/
	static size_t Granularity(){ return granularity; }
	/*in bytes*/
	static size_t TotalPhysMemory(){ return totalPhysMemory; }
	static size_t TotalVirtualMemory(){ return totalVirtualMemory; }
private:
	static size_t pageSize;
	static size_t granularity;
	static size_t totalPhysMemory;
	/*not is OS Virtual Memory, setup by developer */
	static size_t totalVirtualMemory;
	static size_t allocCallCounter;
	static size_t freeCallCounter;
	static bool isInit;
};
#endif