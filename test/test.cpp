// test.cpp : Defines the entry point for the console application.
//


#include "../FlyPartEngine/fpSystem/wndSys/fpWindowSystem.h"
#include "../FlyPartEngine/fpSystem/wndSys/impl/SDL2/fpWindowSDL_GL.h"
#include "../FlyPartEngine/fpSystem/input/impl/SDL2/fpKeyboardSDL.h"
#include "../FlyPartEngine/fpCommon/memory/fpBaseAllocator.h"
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
struct fpMemBlock{

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
	fpBaseMemoryAllocator<test>* allocator = new fpBaseMemoryAllocator<test>(1,false);
	test* v1 = (test*)allocator->Allocate();     v1->x = 1; v1->y = 2; v1->z = 3;
	test* v2 = (test*)allocator->Allocate(); v2->x = 4; v2->y = 5; v2->z = 6;
	test* v3 = (test*)allocator->Allocate(); v3->x = 7; v3->y = 8; v3->z = 9;

    return 0;
}

