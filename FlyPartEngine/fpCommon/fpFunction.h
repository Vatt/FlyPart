
#ifndef FPFUNCTION_H_
#define FPFUNCTION_H_
#pragma once
#include <memory>
template<typename _none> class fpFunction;

template<typename _retType, typename ... _args>
class fpFunction <_retType (_args ...)> {
private:

	class holder
	{
	public:
		holder(){}
		virtual ~holder(){}
		virtual _retType invoke(_args ... args)=0;
		virtual std::shared_ptr<holder> clone()=0;
	private:
		holder(const holder&);
		void operator =(const holder&);
	};

	template<typename _fnSignature>
	class holderFnImpl:public holder
	{
	public:
		holderFnImpl(_fnSignature fn):holder(),_fn(fn){}
		virtual ~holderFnImpl(){}
		virtual std::shared_ptr<holder> clone()
		{

            return  invoker_t(new holderFnImpl(_fn));
		}
		virtual _retType invoke(_args ... args)
		{
			return _fn(args...);
		}
	private:
		_fnSignature _fn;
	};
	template<typename _fnSignature>
	class holderClassMethodImpl: public holder
	{
	};

public:
	fpFunction():_invoker(){};
	~fpFunction(){};
    fpFunction(const fpFunction& other):_invoker(other._invoker->clone()){}

	template<typename _fnSignature>
	fpFunction(_fnSignature fn):_invoker(new holderFnImpl<_fnSignature>(fn)){}
	_retType operator ()(_args ... args)
	{
	
	  return _invoker->invoke(args...);
	}

	void operator = (const fpFunction& other)
	{
        _invoker=other._invoker->clone();
	}
	template<typename fnSignature>
	void operator = (const fnSignature& fn)
	{
		_invoker.reset(new holderFnImpl<fnSignature>(fn));
	}


private:
	typedef std::auto_ptr<holder> invoker_t;
	invoker_t _invoker;

};

#endif /* FPFUNCTION_H_ */
