
#include "../FlyPartEngine/FlyPart.h"

#include "../FlyPartEngine/fpCommon/Containers/fpArray.h"
#include "HeapTester/HeapTester.h"
#include "SmartPtrTest/SmartPtrTest.h"
#ifdef PLATFORM_LINUX
#endif
#ifdef PLATFORM_WINDOWS
	#include <tchar.h>
//	#include "../FlyPartEngine/fpSystem/impl/windows/D3D12/fpD3D12Window.h"
#endif

#include <iostream>
#include <memory>

//using namespace fpTemplate;

int main(int argc, char **argv)
{
	fpMemory::MemoryInitDefault();
	ArrayBase<int> Array(3);
	Array[0] = 3;
	auto i1 = Array[0];
	Array.Resize(1050);
	Array[100] = 100500;
	auto i2 = Array[100];
	auto i3 = Array[0];//TODO: ПОТЕРЯ ЗНАЧЕНИЯ!111
    SmartPtrTest::SmartPtrTestRun();
    fpPlatformMemory::UpdateMemoryStats();
	HeapTester::InitTester(new fpCommonHeap, 65536*8, 0, 1, 32752); //32752);
	HeapTester::RunTests();
	system("PAUSE");
	return 0;
}











