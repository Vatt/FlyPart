// test.cpp : Defines the entry point for the console application.
//


#include "../FlyPartEngine/fpSystem/wndSys/fpWindowSystem.h"
#include "../FlyPartEngine/fpSystem/wndSys/impl/SDL2/fpWindowSDL_GL.h"
#include "../FlyPartEngine/fpSystem/input/impl/SDL2/fpKeyboardSDL.h"
#include <iostream>
#ifdef WIN32
	#include <tchar.h>.
	#define main _tmain
#endif
using namespace std;
struct test
{
        int x, y, z;
        test():x(1),y(2),z(3){}
};
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
   return 0;
}

