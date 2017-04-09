// test.cpp : Defines the entry point for the console application.
//

#include "../FlyPartEngine/FlyPart.h"
//#include "../FlyPartEngine/fpCommon/SmartPtrTest.h"
//#include "../FlyPartEngine/fpCommon/Containers/fpArray.h"
#include "HeapTester.h"
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
    //SmartPtrTest::SmartPtrTestRun();
    //fpMemory::UpdateMemoryStats();
	HeapTester::InitTester(new fpCommonHeap, 65536*8, 0, 1, 32752); //32752);
	HeapTester::RunTests();
	system("PAUSE");
	return 0;
}











