#ifndef _FP_SYSTEM_INCLUDE_
#define _FP_SYSTEM_INCLUDE_
#include "WindowSystem/fpWindowSystem.h"
#include "Input/fpInputSystem.h"
#include "Memory/fpMemorySystem.h"
class fpSystem
{
private:
	static fpWindowSystem* _wndSys;
	static fpInputSystem*  _inputSys;
	static fpMemorySystem* _memorySys;
public:
	static void Init() {}
	static fpWindowSystem* WindowSystem() {
		return _wndSys;
	}
	static fpInputSystem* InputSystem() {
		return _inputSys;
	}
	static fpMemorySystem* Memory() {
		return _memorySys;
	}
};
#endif



