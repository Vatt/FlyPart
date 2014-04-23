#ifndef FPKEYBIND_H
#define FPKEYBIND_H
#include "fpKey.h"
#include "../../util/fpCallback.h"
class fpKeyBind
{
private:
    fpKey _key;
    fpCallbackInterface<void, void>* _callback;
public:
    fpKeyBind(fpKey key, fpCallbackInterface<void, void>* callback);
    void ReBind(fpKey key,fpCallbackInterface<void, void>* callback);
    fpKey getKey();
    fpCallbackInterface<void, void>* getCallback();
};

#endif // FPKEYBIND_H
