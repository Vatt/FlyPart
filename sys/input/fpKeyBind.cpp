#include "fpKeyBind.h"

fpKeyBind::fpKeyBind(fpKey key, fpCallbackInterface<void, void>* callback):
    _key(key),_callback(callback)
{}
void fpKeyBind::ReBind(fpKey key,fpCallbackInterface<void, void>* callback )
{
    _key=key;
    _callback = callback;
}
fpKey fpKeyBind::getKey()
{return _key;}
fpCallbackInterface<void, void>* fpKeyBind::getCallback()
{return _callback;}
