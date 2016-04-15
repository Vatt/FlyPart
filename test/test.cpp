// test.cpp : Defines the entry point for the console application.
//

#include "../FlyPartEngine/FlyPart.h"
#ifdef PLATFORM_LINUX
#endif
#ifdef PLATFORM_WINDOWS
	#include <tchar.h>.
//	#include "../FlyPartEngine/fpSystem/impl/windows/D3D12/fpD3D12Window.h"
#endif



#include <iostream>
#include <memory>

using namespace std;

struct test
{
        int x, y, z;
		test(int x, int y, int z) :x(x), y(y), z(z) {}
        test(test const&  rv)
		{
			x = rv.x;y = rv.y;z = rv.z;
		}
		test(test&& rv)
		{
			x = rv.x;y = rv.y;z = rv.z;
		}
};
/*
void SharedRefTest(fpSharedRef<fpWindowSDL_GL> ref)
{
	fpSharedRef<fpWindowSDL_GL> other = ref;
	cout << "in function ref counter(other): " <<other.GetRefCount() << endl;
	cout << "in function ref counter(ref): " << ref.GetRefCount() << endl;
}
*/
int main(int argc, char **argv)
{
    vector<int> s = {100};
    vector<int> t = {500};
    pair<vector<int>, vector<int>> p(fpTemplate::Move(s), fpTemplate::Move(t));
	//std::shared_ptr<fpWindowSDL_GL> test = std::shared_ptr<fpWindowSDL_GL>(new fpWindowSDL_GL("test3", 50, 651, 800, 600, false));
	/*fpSharedRef<fpWindowSDL_GL> SharedWindow = fpSharedRef<fpWindowSDL_GL>(new fpWindowSDL_GL("test3", 50, 651, 800, 600, false));
	fpWindowSystem* wndSys = fpSystem::_wndSys;
	
	cout << "before function call ref counter: " << SharedWindow.GetRefCount() << endl;
	SharedRefTest(SharedWindow);
	cout << "after function call ref counter: " << SharedWindow.GetRefCount() << endl;
	cout << "fpSharedRef size: "<<sizeof(fpSharedRef<fpWindowSDL_GL>) << endl;
	cout << "std::shared_ptr size: " << sizeof(std::shared_ptr<fpWindowSDL_GL>) << endl;
	wndSys->addWindow(new fpWindowSDL_GL("test", 50, 60, 800, 600, false));
	wndSys->addWindow(new fpWindowSDL_GL("test1", 851, 60, 800, 600, false));
	while (wndSys->wndCount()  > 0)
	{
		wndSys->triggerWndEvent();
	}
	
	*/


    return 0;
}











