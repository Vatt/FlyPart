#ifndef _FP_WINDOW_SYSTEM_INCLUDE_
#define _FP_WINDOW_SYSTEM_INCLUDE_
#include <map>
#include "fpWindow.h"
#include <algorithm>
using namespace std;
class fpWindowSystem
{
private:
	map<int,fpWindow*> _wndList;	
protected:
public:
					fpWindowSystem();
					~fpWindowSystem();
	void 			addWindow(fpWindow* wnd);
	fpWindow* 		getWndById(unsigned int id);
	void 			triggerWndEvent();
	
};
#endif	
