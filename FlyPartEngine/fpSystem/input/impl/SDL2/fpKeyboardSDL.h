

#ifndef FPKEYBOARDSDL_H_
#define FPKEYBOARDSDL_H_
#include "../../../../include/SDL2/SDL.h"
#include "../../fpKeyboard.h"
#include "../../../wndSys/fpWindow.h"



class fpKeyboardSDL: public fpKeyboard
{
private:

	fpKeyboardSDL();
	fpKeyboardSDL(const fpKeyboardSDL&);

public:

    fpKeyboardSDL(fpWindow* attachedWnd);
	~fpKeyboardSDL();


private:


};

#endif /* FPKEYBOARDSDL_H_ */
