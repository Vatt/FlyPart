
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
	Test(int32 x, int32 y, int32 z) :x(x), y(y), z(z) {}
	Test() :x(++Counter), y(++Counter), z(++Counter) {}
	void SelfPrint() const
	{
		std::cout << "x:" << x << " y:" << y << " z:" << z << std::endl;
	}
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

	fpArray<Test> Array = { Test(),Test(),Test() }; ;// {5, 8, 7, 9, 7, 5, 2, 6};//
	Array.PushBack(Test());
	Array.PushBack(Test());
	Array.PushBack(Test());
	//на линухе сниз ошибка
	//Test& a1 = Array.Pop(); 
	//Array.PushFront(a1);
	Array.Insert(1, Test());
	Array.EmplaceBack(100, 200, 300);
	for (uint32 index = 0;index<Array.Length();index++)
	{
		Array[index].SelfPrint();
	}

	//for (uint32 index = 0; index<Array.Length(); index++)
	//{
	//	std::cout << Array[index] << endl;;
	//}
	system("PAUSE");
	return 0;
}











