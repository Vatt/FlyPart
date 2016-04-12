
#include "fpD3D12Window.h"
#include "../../../fpCommon/fpSharedPtr.h"
//fpSharedRef<int> shared = fpSharedRef(1);
fpD3D12Window::fpD3D12Window(void) { }
fpD3D12Window::fpD3D12Window( const char* name, unsigned int x, unsigned int y,unsigned int width, unsigned int height, bool fullscreen)
{
	createWindow(name, x, y, width, height, fullscreen);
}
void fpD3D12Window::createWindow( const char* name, unsigned int x, unsigned int y, unsigned int width, unsigned int height, bool fullscreen)
{

	
	_height = height;
	_width = width;
	_x = x;
	_y = y;

	_name = name;
	_deleted = false;
	_fullscreen = fullscreen;
	_minimize = false;





	switchFullscreen(fullscreen);
	showWindow();


}

void fpD3D12Window::showWindow()
{

}
void fpD3D12Window::resize(unsigned int width, unsigned int height)
{
	
}
bool fpD3D12Window::switchFullscreen(bool flag)
{
	return false;
	
}
void fpD3D12Window::minimizeWindow()
{

	_minimize = true;
}

void fpD3D12Window::deleteWindow()
{

	_deleted = true;
}
void fpD3D12Window::hideWindow()
{

	_hidden = true;
}
fpD3D12Window::~fpD3D12Window()
{
	deleteWindow();
}
void fpD3D12Window::maximizeWindow()
{

	_minimize = false;
	
}
void fpD3D12Window::triggerEvent()
{


}

