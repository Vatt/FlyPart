#ifndef _FP_ENGINE_MODULE_INTERFACE_
#define _FP_ENGINE_MODULE_INTERFACE_


struct fpModuleInterface
{
private:
	const char * name;
	bool isLoaded;
public:
	fpModuleInterface(const char* name)
	{
		//fpCrc32Helper.Gen(name);
		//meta_info.add(this);
	}
	const char* getName()
	{
		return name;
	}
	fpModuleInterface* QueryInterface()
	{
		return this;
	}
	virtual void Initialize() = 0;
	virtual void Shutdown() = 0;
};
#endif