#ifndef _FP_SYSTEM_INCLUDE_
#define _FP_SYSTEM_INCLUDE_
#include "WindowSystem/fpWindowSystem.h"
//#include "Input/fpInputSystem.h"
struct fpSystem
{
public:
	static fpWindowSystem* _wndSys;
	//fpInputSystem*  _inputSys;
};
fpWindowSystem* fpSystem::_wndSys = new fpWindowSystem();
#endif



