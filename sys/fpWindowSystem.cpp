
#include "fpWindowSystem.h"
fpWindowSystem::fpWindowSystem()
{}
fpWindowSystem::~fpWindowSystem()
{}

fpWindow* fpWindowSystem::getWndById(unsigned int id)
{
	if (id > _wndList.size()||id<0)
	{
		
	}
	return _wndList[id];
	
	
}
void fpWindowSystem::addWindow(fpWindow* wnd)
{
	
	if (wnd->getId() < 0)
	{

	}else 	_wndList.insert(std::make_pair(wnd->getId(), wnd));
}
void fpWindowSystem::triggerWndEvent()
{

	//for(auto pair:_wndList)
	for (map<int, fpWindow*>::iterator i=_wndList.begin(); i != _wndList.end(); i++)
	{
		if (!i->second->isDeleted())
		{
			i->second->triggerEvent();
		}
		else
		{
			i = _wndList.erase(i); //TODO: 
			if (_wndList.size() == 0)return;
		}
	}
}
