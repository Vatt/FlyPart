
#include "fpWindowSDL_GL.h"

fpWindowSDL_GL::fpWindowSDL_GL(void) { }
fpWindowSDL_GL::fpWindowSDL_GL( const char* name, unsigned int x, unsigned int y,unsigned int width, unsigned int height, bool fullscreen)
{
	createWindow(name, x, y, width, height, fullscreen);
}
void fpWindowSDL_GL::createWindow( const char* name, unsigned int x, unsigned int y, int width, unsigned int height, bool fullscreen)
{
	SDL_Init(SDL_INIT_VIDEO);//TODO: вынести на уровень выше
	
	_height = height;
	_width = width;
	_x = x;
	_y = y;

	_name = name;
	_deleted = false;
	_fullscreen = fullscreen;
	_minimize = false;
	wnd = SDL_CreateWindow(name, _x, _y, _width, _height, SDL_WINDOW_RESIZABLE);
	if (!wnd)
	{
		//TODO:вставить ошибку сюда
	}
	_id=SDL_GetWindowID(wnd);
	switchFullscreen(fullscreen);
	showWindow();


}

void fpWindowSDL_GL::showWindow()
{
	SDL_ShowWindow(wnd);
}
void fpWindowSDL_GL::resize(unsigned int width, unsigned int height)
{
	SDL_SetWindowSize(wnd, width, height);
}
bool fpWindowSDL_GL::switchFullscreen(bool flag)
{
	if (flag)
	{
		if (SDL_SetWindowFullscreen(wnd, SDL_WINDOW_FULLSCREEN) != 0)
		{
			//TODO:вытащить ошибки из SDL_Err
			return false;
		}
	}
	if (!flag)
	{
		if (SDL_SetWindowFullscreen(wnd, 0) != 0)
		{
			//TODO: вытащить ошибки из SDL_Err
			return false;
		}
	}
	return true;
	
}
void fpWindowSDL_GL::minimizeWindow()
{
	SDL_MinimizeWindow(wnd);
	_minimize = true;
}

void fpWindowSDL_GL::deleteWindow()
{
	SDL_DestroyWindow(wnd);
	SDL_GL_DeleteContext(context);
	_deleted = true;
}
void fpWindowSDL_GL::hideWindow()
{
	SDL_HideWindow(wnd);
	_hidden = true;
}
fpWindowSDL_GL::~fpWindowSDL_GL()
{
	deleteWindow();
}
void fpWindowSDL_GL::maximizeWindow()
{
	SDL_MaximizeWindow(wnd);
	SDL_GetWindowPosition(wnd, &_x, &_y);
	SDL_GetWindowSize(wnd,&_width, &_height);
	_minimize = false;
	
}
void fpWindowSDL_GL::triggerEvent()
{

    SDL_Event* wndEvents=new SDL_Event[100];
    int index=0;
    int countEvents=SDL_PeepEvents(wndEvents,20,SDL_PEEKEVENT,SDL_WINDOWEVENT,SDL_SYSWMEVENT);
        //while (SDL_PollEvent(&event))
          while(index<countEvents)
          {
            if (wndEvents[index].window.windowID == _id)
            {
                switch (wndEvents[index].window.event)
                {
                    case  SDL_WINDOWEVENT_RESIZED:
                        resize(wndEvents[index].window.data1, wndEvents[index].window.data2);

                        break;
                    case SDL_WINDOWEVENT_HIDDEN:
                        hideWindow();
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        deleteWindow();
                        break;
                    case SDL_QUIT:
                        SDL_Quit();
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        maximizeWindow();
                        break;
                    case SDL_WINDOWEVENT_MOVED :
                        _x = wndEvents[index].window.data1;
                        _y = wndEvents[index].window.data2;
                        break;
                    default:
                        break;
					}

            }
            index++;
		}
          delete[] wndEvents;
}

