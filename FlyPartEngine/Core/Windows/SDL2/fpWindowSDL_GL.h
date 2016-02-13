
#ifndef _FP_WINDOW_SDL_INCLUDE_
#define _FP_WINDOW_SDL_INCLUDE_
#include "../../GenericPlatform/Window/fpWindow.h"
#include <SDL2/SDL.h>
#include <iostream>

class fpWindowSDL_GL : public  fpWindow
{
private:
	SDL_Window* wnd = nullptr;
	SDL_GLContext context = nullptr;


public:
	fpWindowSDL_GL( const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool fullscreen);
	fpWindowSDL_GL(void);
	~fpWindowSDL_GL();
	void createWindow( const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool fullscreen) override;
	bool switchFullscreen(bool flag) override;
	void showWindow() override;
	void deleteWindow() override;
	void minimizeWindow() override;
	void maximizeWindow() override;
	void hideWindow() override;
	void resize(unsigned int width, unsigned int height) override;
	void triggerEvent() override;
	std::string str;
};

#endif
