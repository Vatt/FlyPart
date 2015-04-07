
#include "fpWindowSDL_GL.h"
#include <iostream>
using namespace std;
fpWindowSDL_GL::fpWindowSDL_GL(void) { }
fpWindowSDL_GL::fpWindowSDL_GL( const char* name, unsigned int x, unsigned int y,unsigned int width, unsigned int height, bool fullscreen)
{
	createWindow(name, x, y, width, height, fullscreen);
}
void fpWindowSDL_GL::createWindow( const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool fullscreen)
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
	wnd = SDL_CreateWindow(name, _x, _y, _width, _height, SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,3);
	context =  SDL_GL_CreateContext(wnd);
	SDL_GL_SwapWindow(wnd);

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

    SDL_Event* events=new SDL_Event[100];

    int index=0;
    SDL_PumpEvents();
    int countEvents=SDL_PeepEvents(events,100,SDL_PEEKEVENT,SDL_WINDOWEVENT,SDL_SYSWMEVENT);
        //while (SDL_PollEvent(&event))
          while(index<countEvents)
          {
            cout<<"wndID: "<<events[index].window.windowID<<" count: "<<countEvents<<endl;
            if (events[index].window.windowID == _id)
            {
                switch (events[index].window.event)
                {
                    case  SDL_WINDOWEVENT_RESIZED:
                        resize(events[index].window.data1, events[index].window.data2);
                        cout<<"SDL_WINDOWEVENT_RESIZED"<<endl;
                        break;
                    case SDL_WINDOWEVENT_HIDDEN:
                        hideWindow();
                        cout<<"SDL_WINDOWEVENT_HIDDEN"<<endl;
                        break;
                    case SDL_WINDOWEVENT_CLOSE:
                        deleteWindow();
                        cout<<"SDL_WINDOWEVENT_CLOSE"<<endl;
                        break;
                    case SDL_QUIT:
                        SDL_Quit();
                        cout<<"SDL_QUIT"<<endl;
                        deleteWindow();
                        break;
                    case SDL_WINDOWEVENT_MAXIMIZED:
                        maximizeWindow();
                        cout<<"SDL_WINDOWEVENT_MAXIMIZED"<<endl;
                        break;
                    case SDL_WINDOWEVENT_MOVED :
                      cout<<"SDL_WINDOWEVENT_MOVED"<<endl;
                        _x = events[index].window.data1;
                        _y = events[index].window.data2;
                        break;
                    default:
                        break;
					}

            }
            index++;
		}
	  delete events;
}

