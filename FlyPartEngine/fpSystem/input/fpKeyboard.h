

#ifndef FPKEYBOARD_H_
#define FPKEYBOARD_H_

#include "../../fpCommon/fpCallback.h"
#include "../wndSys/fpWindow.h"
#include "fpKeyBind.h"




class fpKeyboard {
private:
	fpKeyboard(const  fpKeyboard &);
protected:
	fpKeyboard(){};
    fpWindow* _wnd;

public:

                        fpKeyboard(fpWindow* wnd);
    virtual             ~fpKeyboard();

private:
    bool          isStreamMode;

};

#endif /* FPKEYBOARD_H_*/
