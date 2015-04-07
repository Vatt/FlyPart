#ifndef _FP_SYSTEM_INCLUDE_
#define _FP_SYSTEM_INCLUDE_
#include "WindowSystem/fpWindowSystem.h"
#include "Input/fpInputSystem.h"
class fpSystem
{
private:
	static fpWindowSystem* _wndSys;
	static fpInputSystem*  _inputSys;
public:
	static void Initialize() {}
	static fpWindowSystem* WindowSystem() {
		return _wndSys;
	}
	static fpInputSystem* InputSystem() {
		return _inputSys;
	}
};
#endif



