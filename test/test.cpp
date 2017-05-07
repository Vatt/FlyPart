
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
	Test(Test&& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		other.x = -1;
		other.y = -1;
		other.z = -1;
	}
	Test(const Test& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	Test& operator=(const Test& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		return *this;
	}
	Test& operator=(Test&& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
		other.x = -1;
		other.y = -1;
		other.z = -1;
		return *this;
	}
	bool operator==(const Test& other)
	{
		return x == other.x && y == other.y && z == other.z;
	}
	friend bool operator==(const Test& Lhs, const Test& Rhs)
	{
		return Lhs.x == Rhs.x && Lhs.y == Rhs.y && Lhs.z == Rhs.z;
	}
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
	fpArray<Test> Array1(fpArray<Test>({ Test(),Test(),Test() }));
	
	Array.PushBack(Test());
	Array.PushBack(Test());
	Array.PushBack(Test());
	//на линухе сниз ошибка
	Test& a1 = Array[4]; 
	
	

	Array.Insert(Array1, 3);
	Array.Insert({ Test(),Test(),Test() }, Array.Length());
	fpArray<Test> Array2 = { Test(),Test() };
	Array.Insert(Array2.GetData(), Array2.Length(), Array.Length());
	//for (auto it : Array)
	//{
	//	it.SelfPrint();
	//}
	uint32 Index;
	bool find_res = Array.FindLast(a1, Index);
	int32 find_pre = Array.Find([&](const Test& t) {return t.x==13 && t.y==14&&t.z==15; },3);
	auto filtered = Array.Filter([&](const Test& t) 
	{
		return t.x%7==0 || t.y%7==0 || t.z%7==0; 
	});
	for (auto it = Array.CreateReverseIterator(); it; --it)
	{
		it->SelfPrint();
	}
	std::cout << "----------------------------------------" <<std::endl;
	for (auto item : filtered)
	{
		item.SelfPrint();
	}
	
	system("PAUSE");
	return 0;
}











