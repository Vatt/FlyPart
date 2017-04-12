
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
	ArrayBase<int> Array(ArrayBase<int>(3));
	fpIndexedIterator<ArrayBase<int>, int, int> iterator(Array,0);
	Array[0] = 1;
	Array[1] = 2;
	Array[2] = 3;
	auto v1 = iterator.operator*();
	auto v2 = ++iterator.operator*();
	auto v3 = ++iterator.operator*();
	Array.Resize(4);
	Array[3] = 4;
	auto v4 = ++iterator.operator*();
	std::allocator<int> a;
    SmartPtrTest::SmartPtrTestRun();
    fpPlatformMemory::UpdateMemoryStats();
	HeapTester::InitTester(new fpCommonHeap, 65536*8, 0, 1, 32752); //32752);
	HeapTester::RunTests();
	system("PAUSE");
	return 0;
}











