// test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#include "../FlyPartEngine/fpCommon/typedefs.h"
#ifdef _WIN32
	#include <tchar.h>.
	#include <Windows.h>
	#include <Psapi.h>
	#define main _tmain
#endif
#include <stddef.h>
using namespace std;

struct test
{
        int x, y, z;
		test()
		{
			x = 1;y = 2;z = 3;
		}
};

typedef unsigned char uchar;
int main(int argc, char **argv)
{
	/*fpWindowSystem* wndSys = new fpWindowSystem();
	fpWindow* wnd = new fpWindowSDL_GL("test", 50, 60, 800, 600, false);
	wndSys->addWindow(wnd);
	while (wndSys->_wndList.size() > 0)
	{
		wndSys->triggerWndEvent();
	}
	*/
	struct FreeMem
	{
		FreeMem* next;
		uint32 numFreeBlocks;
	};
	size_t sz = sizeof(FreeMem);

    return 0;
}











