#include "../FlyPartEngine/FlyPart.h"

#include "../FlyPartEngine/fpCommon/fpCommon.h"
//#include "../FlyPartEngine/fpCommon/Containers/fpList.h"
#include "HeapTester/HeapTester.h"
#include "SmartPtrTest/SmartPtrTest.h"
#include "ContainerTester/fpArray/fpArrayTester.h"
#ifdef PLATFORM_LINUX
#endif
#ifdef PLATFORM_WINDOWS
	#include <tchar.h>
//	#include "../FlyPartEngine/fpSystem/impl/windows/D3D12/fpD3D12Window.h"
#endif

#include <iostream>
//#include <list>
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
	Test& operator=(Test&&  other)
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
const int cval = 8;
int main(int argc, char **argv)
{
	fpMemory::MemoryInitDefault();

	//SmartPtrTest::SmartPtrTestRun();
	/*
	fpPlatformMemory::UpdateMemoryStats();
	HeapTester::InitTester(fpMemory::GetCommonHeap(), 65536*10, 0, 1, 32752);
	HeapTester::RunTests();
	*/
	
	fpArrayTester ArrayTester(50);
	ArrayTester.RunPushTest();
	/*
	std::cout << "---------------fpArray BEGIN------------" <<std::endl;
	fpArray<Test> Array = { Test(),Test(),Test() }; ;// {5, 8, 7, 9, 7, 5, 2, 6};//
	fpArray<Test> Array1(fpArray<Test>({ Test(),Test(),Test() }));
	Array.PushBack(Test());
	Array.PushBack(Test());
	Array.PushBack(Test());
	Test& a1 = Array[4];


    //TODO: на самом деле ГЦЦ тут прав, сигнатура принимает константный адрес
	Array.Insert(static_cast<const fpArray<Test>&>(Array1), 3);
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
	//TODO: Реверс выглядит не так, сделат ькак с листом
	for (auto it = Array.CreateReverseIterator(); it; it--)
	{
		it->SelfPrint();
	}
	std::cout << "--------------------------------------" <<std::endl;
	for (auto item : filtered)
	{
		item.SelfPrint();
	}
    std::cout << "---------------fpArray END------------" <<std::endl;

	std::cout << "----------------fpLinkedList BEGIN-------------" <<std::endl;
    fpLinkedList<Test> List;
    List.PushBack(Test());
    List.PushBack(Test());
    List.PushBack(Test());
	List.EmplaceFront(88, 99, 111);
	List.EmplaceBack (120, 130, 140);
	List.LinkAfter(List.Front(), Test());
	List.LinkBefore(List.Front(), 0, 0, 0);
	List.LinkBefore(List.Back(), 2, 2, 2);
	List.LinkAfter(List.Back(), 1, 1, 1);
	//List.Clear();
	std::cout << "----------------fpLinkedList TEST REVERSE ITERATOR-------------" << std::endl;
    for (auto list_it = List.CreateReverseIterator();list_it;list_it++)
    {
        list_it->SelfPrint();
    }
	std::cout << "----------------fpLinkedList TEST DEFAULT ITERATOR-------------" << std::endl;
	for (auto list_it = List.CreateIterator(); list_it; list_it++)
	{
		list_it->SelfPrint();
	}
	auto finded_node_p = List.FindNode([&](Test& test) {return test.z == 51; });
	Test finded_node_v;
	bool finded_node_b = List.Find([&](Test& test) {return test.z == 48; }, finded_node_v);
	
    auto finded_node_p_l = List.FindLastNode([&](Test& test) {return test.x == 43; });  
    //finded_node_p_l->Data.SelfPrint();
    
    Test finded_node_v_l;
	bool finded_node_b_l = List.FindLast([&](Test& test) {return test.x == 43; }, finded_node_v_l);
	//finded_node_v_l.SelfPrint();
	List.FindNode(finded_node_v_l);
	List.Contains(finded_node_v);
	List.Remove(finded_node_v_l);
	List.Remove([&](Test& test) {return test.z == 54; });
	std::cout << "----------------fpLinkedList TEST REMOVE-------------" << std::endl;
    for(auto item:List)
    {
        item.SelfPrint();
    }
    */
    
	std::cout << "----------------fpLinkedList END-------------" <<std::endl;
    system("PAUSE");
	return 0;
}











