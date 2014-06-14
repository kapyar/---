#ifndef _Functor_H
#define _Functor_H


#include <iostream>
#include <memory>
using namespace std;
#include "TypeList.h"




namespace Private{

template<typename R>
struct FunctorImplBase
{
	typedef R ResultType;
	typedef EmptyType Parm1;
	typedef EmptyType Parm2;
	typedef FunctorImplBase<R> FunctorImplBaseType;
	virtual ~FunctorImplBase(){};
};
};

//forward declaration
template<typename R,class TList>
class FunctorImpl;

//no parametr
template<typename R>
class FunctorImpl<R,NullType>
	:public Private::FunctorImplBase<R>
{
public:
	typedef R ResultType;
	virtual R operator()() = 0;

};

//one parametr
template<typename R, typename P1>
class FunctorImpl<R,TYPELIST_1(P1)>
	:public Private::FunctorImplBase<R>
{
public:
	typedef R ResultType;
	typedef P1 Parm1;
	virtual R operator()(Parm1) = 0;

};

//two parametrs
template<typename R, typename P1, typename P2>
class FunctorImpl<R,TYPELIST_2(P1,P2)>
	:public Private::FunctorImplBase<R>
{
public:
	typedef R ResultType;
	typedef P1 Parm1;
	typedef P2 Parm2;
	virtual R operator()(Parm1,Parm2) = 0;
	
};

//Functor handler

template<class ParentFunctor, typename Fun>
class FunctorHandler
	:public FunctorImpl
	<
		typename ParentFunctor::ResultType,
		typename ParentFunctor::ParmList
	>
	
	
{
	typedef typename ParentFunctor::Impl Base;
public:
	typedef typename Base::ResultType ResultType;
	typedef typename Base::Parm1 Parm1;
	typedef typename Base::Parm2 Parm2;

	FunctorHandler(const Fun& fun):_fun(fun){}
	
	ResultType operator()()
	{
		return _fun();
	}

	ResultType operator()(Parm1 p1)
	{
		return _fun(p1);
	}

	ResultType operator()(Parm1 p1,Parm2 p2)
	{
		return _fun(p1,p2);
	}

	private:
		Fun _fun;
};

template<typename R,class TList>
class Functor
{
	
public:
	
	typedef FunctorImpl<R,TList> Impl;
	typedef R ResultType;
	typedef TList ParmList;
	typedef typename Impl::Parm1 Parm1;
	typedef typename Impl::Parm2 Parm2;
	
	Functor():_spImpl(0){};
	
	template<typename Fun>
	Functor(Fun fun)
		:_spImpl(new FunctorHandler<Functor,Fun>(fun)){}

	explicit Functor(auto_ptr<Impl> spImpl):_spImpl(spImpl){};

	R operator()()
	{
		return (*_spImpl)();
	}
	R operator()(Parm1 p1)
	{
		return (*_spImpl)(p1);
	}
	R operator()(Parm1 p1, Parm2 p2)
	{
		return (*_spImpl)(p1,p2);
	}
private:
	Functor& operator=(const Functor&);
	Functor(const Functor&);
	auto_ptr<Impl> _spImpl;
};
#endif