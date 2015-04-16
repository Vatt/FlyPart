// test.cpp : Defines the entry point for the console application.
//

#include <iostream>
#ifdef _WIN32
	#include <tchar.h>.
	#include <Windows.h>
	#include <Psapi.h>
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
	/*fpWindowSystem* wndSys = new fpWindowSystem();
	fpWindow* wnd = new fpWindowSDL_GL("test", 50, 60, 800, 600, false);
	wndSys->addWindow(wnd);
	while (wndSys->_wndList.size() > 0)
	{
		wndSys->triggerWndEvent();
	}
	*/
    cout<<"unsigned int: "<<sizeof(unsigned int)<<endl;
    cout<<"unsigned long long int: "<<sizeof(unsigned long long int)<<endl;
    cout<<"long long int: "<<sizeof(long long int)<<endl;
    cout<<"long int: "<<sizeof(long int)<<endl;
    cout<<"short: "<<sizeof(short)<<endl;
    cout<<"unsigned short: "<<sizeof(unsigned short)<<endl;
	cout << "int: " << sizeof(int) << endl;
    return 0;
}











