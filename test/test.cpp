// test.cpp : Defines the entry point for the console application.
//


#include "../FlyPartEngine/fpSystem/fpSystemInterface.h"
#include "../FlyPartEngine/fpSystem/impl/linux/SDL2/fpWindowSDL_GL.h"
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

typedef unsigned char uchar;
int main(int argc, char **argv)
{
	fpWindowSystem* wndSys = fpSystem::_wndSys;
	fpWindow* wnd = new fpWindowSDL_GL("test", 50, 60, 800, 600, false);
	fpWindow* wnd1 = new fpWindowSDL_GL("test", 50, 60, 800, 600, false);
	wndSys->addWindow(wnd); wndSys->addWindow(wnd1);
	while (wndSys->wndCount()  > 0)
	{
		wndSys->triggerWndEvent();
	}


    return 0;
}











