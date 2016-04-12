
#ifndef _FP_WINDOW_SDL_INCLUDE_
#define _FP_WINDOW_SDL_INCLUDE_
#include "../../GenericPlatform/Window/fpWindow.h"


class fpD3D12Window : public  fpWindow
{
private:



public:
	fpD3D12Window( const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool fullscreen);
	fpD3D12Window(void);
	~fpD3D12Window();
	void createWindow( const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool fullscreen) override;
	bool switchFullscreen(bool flag) override;
	void showWindow() override;
	void deleteWindow() override;
	void minimizeWindow() override;
	void maximizeWindow() override;
	void hideWindow() override;
	void resize(unsigned int width, unsigned int height) override;
	void triggerEvent() override;
//	std::string str;
};

#endif
