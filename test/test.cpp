// test.cpp : Defines the entry point for the console application.
//

#include "../FlyPartEngine/FlyPart.h"
#include "../FlyPartEngine/fpCommon/SmartPtrTest.h"
#ifdef PLATFORM_LINUX
#endif
#ifdef PLATFORM_WINDOWS
	#include <tchar.h>
//	#include "../FlyPartEngine/fpSystem/impl/windows/D3D12/fpD3D12Window.h"
#endif



#include <iostream>
#include <memory>

using namespace std;
using namespace fpTemplate;
int main(int argc, char **argv)
{
    SmartPtrTest::SmartPtrTestRun();
    fpMemory::UpdateMemoryStats();
    void* raw_mem = fpMemory::SystemAlloc(4096);
    auto ps = fpMemory::Stats.PageSize;
    auto totalMem = fpMemory::Stats.TotalPhysMemory/1024/1024;
    auto freeMem  = fpMemory::Stats.AvailablePhysMemory/1024/1024;
    auto memLimit = fpMemory::Stats.MemoryLimit;

    return 0;
}











