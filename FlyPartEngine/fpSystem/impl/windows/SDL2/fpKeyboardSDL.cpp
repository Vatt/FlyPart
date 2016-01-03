
#include "fpKeyboardSDL.h"
#include <iostream>

/*
fpKeyboardSDL::fpKeyboardSDL(fpWindow* attachedWnd):fpKeyboard(attachedWnd)
{



}

fpKeyboardSDL::~fpKeyboardSDL() {
	// TODO Auto-generated destructor stub
}
const char* fpKeyboardSDL::getTextStream()
{
    SDL_Event* events=new SDL_Event[100];
    int countEvents=0;
    int index=0;


    if(SDL_GetWindowID(SDL_GetKeyboardFocus()) == _wnd->getId())
    {
        countEvents=SDL_PeepEvents(events,20,SDL_GETEVENT,SDL_KEYDOWN,SDL_TEXTINPUT);
        while(index<countEvents)
        {

            index++;
            switch (events->key.keysym.scancode)
            {
              default:std::cout<<events->key.keysym.sym<<std::endl;
            }
        }
    }
    delete[] events;
}*/


