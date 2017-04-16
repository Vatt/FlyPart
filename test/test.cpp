
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

//using namespace fpTemplate;
struct Test {
	static int32 Counter;
	int32 x, y, z;
	Test() :x(++Counter), y(++Counter), z(++Counter) {}
	~Test() { x = -1; y = -1; z = -1; }
};
int32 Test::Counter = 0;
int main(int argc, char **argv)
{
	fpMemory::MemoryInitDefault();
	//std::allocator<int> a;
	//SmartPtrTest::SmartPtrTestRun();
	//fpPlatformMemory::UpdateMemoryStats();
	//HeapTester::InitTester(fpMemory::GetCommonHeap(), 65536*10, 0, 1, 32752);
	//HeapTester::RunTests();

	fpArray<Test> Array(5);
	for (auto i = 0; i < 6; i++)
	{
		//Array[i] = i;
	}
	auto a1 = Array.Pop();
	bool vt = fpIsPODType<Test>::Value;
	auto sz = sizeof(Test);
	system("PAUSE");
	return 0;
}











