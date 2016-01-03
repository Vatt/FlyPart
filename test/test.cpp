// test.cpp : Defines the entry point for the console application.
//

#include "../FlyPartEngine/fpSystem/fpSystemInterface.h"
#include "../FlyPartEngine/fpCommon/fpSharedPtr.h"
#ifdef PLATFORM_LINUX
	#include "../FlyPartEngine/fpSystem/impl/linux/SDL2/fpWindowSDL_GL.h"
#endif
#ifdef PLATFORM_WINDOWS
	#include "../FlyPartEngine/fpSystem/impl/windows/SDL2/fpWindowSDL_GL.h"
//	#include "../FlyPartEngine/fpSystem/impl/windows/D3D12/fpD3D12Window.h"
#endif
#include <iostream>
#ifdef WIN32
	#include <tchar.h>.
	#define main _tmain
#endif
using namespace std;

struct test
{
        int x, y, z;
};


int main(int argc, char **argv)
{
	fpSharedRef<fpWindowSDL_GL> shared_wnd =  fpSharedRef<fpWindowSDL_GL>(new fpWindowSDL_GL("test", 50, 60, 800, 600, false));
	fpSharedRef<fpWindowSDL_GL> shared_wnd2 = fpSharedRef<fpWindowSDL_GL>(new fpWindowSDL_GL("test1",851, 60, 800, 600, false));
	fpWindowSystem* wndSys = fpSystem::_wndSys;
	wndSys->addWindow(&shared_wnd.GetRef());
	wndSys->addWindow(&shared_wnd2.GetRef());
	while (wndSys->wndCount()  > 0)
	{
		wndSys->triggerWndEvent();
	}


    return 0;
}











