#pragma once
#ifndef _FP_WINDOWS_MEMORY_
#define _FP_WINDOWS_MEMORY_
#include "../fpMemory.h"
class fpWindowsMemory : public fpMemory
{
public:
	fpWindowsMemory();
	virtual void* SystemAlloc(size_t size) override;
	virtual void SystemFree(void* ptr) override;
	virtual fpAllocator* DefaultAllocator() override;
	
};
#endif