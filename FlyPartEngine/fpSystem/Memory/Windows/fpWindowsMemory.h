#pragma once
#ifndef _FP_WINDOWS_MEMORY_
#define _FP_WINDOWS_MEMORY_
#include "../fpMemory.h"
#include <Windows.h>
class fpWindowsMemory : public fpPlatformMemory
{
public:
	fpWindowsMemory();
	virtual void* SystemAlloc(size_t size) override;
	virtual void SystemFree(void* ptr) override;
	virtual void UpdateMemoryStats() override;
	
};
#endif