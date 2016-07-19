#ifndef _FP_WINDOW_SYSTEM_INCLUDE_
#define _FP_WINDOW_SYSTEM_INCLUDE_
#include <map>
#include "fpWindow.h"
#include <algorithm>
#include "../typedefs.h"
using namespace std;
class fpWindowSystem
{
private:
	map<int,fpWindow*> _wndList;	
protected:
public:
	fpWindowSystem();
	virtual ~fpWindowSystem();
	virtual void 			addWindow(fpWindow* wnd);
	virtual fpWindow* 		getWndById(unsigned int id);
	virtual void 			triggerWndEvent();
	virtual uint32			wndCount();
	
};
#endif	
