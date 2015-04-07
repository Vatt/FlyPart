
#ifndef _FP_CALLBACK_INCLUDE_
#define _FP_CALLBACK_INCLUDE_


template<typename _retType, typename ... _args>
class fpCallbackInterface
{
private:
	fpCallbackInterface(const fpCallbackInterface&);
	void operator=(const fpCallbackInterface&);
public:
	fpCallbackInterface(){};
	virtual ~fpCallbackInterface(){};
	virtual _retType exec(_args ... args) = 0;
};
template<typename _retType,typename ... _args>
class fpCallbackFunction :public fpCallbackInterface<_retType,_args ...>
{
private:
	_retType(*_ptrFn)(_args ... args);
public:
	fpCallbackFunction()
	{
		_ptrFn=nullptr;
	};
	~fpCallbackFunction(){};
	fpCallbackFunction( _retType(*ptrFn)(_args ... args))
	{
		_ptrFn = ptrFn;
	}
	_retType exec(_args ... args)
	{
		return _ptrFn(args ...);
	}
};
template<typename _retType, class  cl, typename ... _args >
class fpCallbackMethod:public fpCallbackInterface<_retType,_args...>
{
private:
	_retType(cl::*_ptrMethod)(_args ... args);
	cl* _ptrClass;
	fpCallbackMethod();
	fpCallbackMethod(fpCallbackMethod& callback);
public:

	~fpCallbackMethod(){}
	fpCallbackMethod(cl* ptrClass, _retType (cl::* ptrMethod)(_args ... args) )
	{
		_ptrMethod = ptrMethod;
		_ptrClass = ptrClass;
	}
	_retType exec(_args ... args)
	{
		return (_ptrClass->*_ptrMethod)(args ...);
	}
};
#endif
