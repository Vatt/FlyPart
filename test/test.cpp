#include "../FlyPartEngine/FlyPart.h"

#include "../FlyPartEngine/fpCommon/fpCommon.h"
#include "HeapTester/HeapTester.h"
#include "ContainerTester/fpArray/fpArrayTester.h"
#ifdef PLATFORM_LINUX
#endif
#ifdef PLATFORM_WINDOWS
	#include <tchar.h>
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

	/*
	fpPlatformMemory::UpdateMemoryStats();
	HeapTester::InitTester(fpMemory::GetCommonHeap(), 65536*10, 0, 1, 32752);
	HeapTester::RunTests();
	*/
	
	fpArrayTester::InitTester(495);
	fpArrayTester::RunPushTest();
    system("PAUSE");
	return 0;
}











