#ifndef _FP_SYSTEM_INCLUDE_
#define _FP_SYSTEM_INCLUDE_
#include "fpWindowSystem.h"
#include "fpInputSystem.h"
#include "../util/fpFunction.h"
class fpSystemInterface
{
public:
	enum  state { RUNNING = 1, PAUSE = 0, START = -1 };
private:
	state _sysState;
	fpWindowSystem* _wndSys;
	fpInputSystem*  _inputSys;
    fpFunction<void(void)> extensionInitFn;
public:

	fpSystemInterface();
	virtual ~fpSystemInterface();

    void setExtensionInitFn(const fpFunction<void ()> &value);
};
#endif



void fpSystemInterface::setExtensionInitFn(const fpFunction<void ()> &value)
{
    extensionInitFn = value;
}
