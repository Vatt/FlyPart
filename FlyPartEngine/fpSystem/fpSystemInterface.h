#ifndef _FP_SYSTEM_INCLUDE_
#define _FP_SYSTEM_INCLUDE_
#include "wndSys/fpWindowSystem.h"
#include "input/fpInputSystem.h"
#include "../fpCommon/fpFunction.h"
struct fpSystemInterface
{
public:
	fpWindowSystem* _wndSys;
	fpInputSystem*  _inputSys;
};
#endif



