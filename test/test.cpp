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
    return 0;
}











