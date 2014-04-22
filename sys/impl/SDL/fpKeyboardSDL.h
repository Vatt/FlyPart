/*
 * fpKeyboardSDL.h
 *
 *  Created on: 26 февр. 2014 г.
 *      Author: gamover
 */

#ifndef FPKEYBOARDSDL_H_
#define FPKEYBOARDSDL_H_
#include "SDL2/SDL.h"
#include "../../input/fpKeyboard.h"



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
