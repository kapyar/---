#ifndef _DeferredString_h_
#define _DeferredString_h_

#define NDEBUG

#include <string>
#include <iostream>
#include<cassert>
using namespace std;

template<class T>
class DeferredString;

template<class T>
class DeferredString
{
	//friend void tester(const DeferredString&);
private:
//	Representation of a shared string
	struct StringRep;
	StringRep* _rep;
//	Proxy class for a character in the string
	class CharProxy;
	void checkForSpace()
	{
		if (_rep == 0)
			throw BadString("No more space in the system");
	}
	void check(size_t i) const
	{
//	check if the index is within of the range
		if (i<0||_rep->_len<=i)
		{
			throw BadString("Bad Index");
		}
	return;
	};
	
	T read(int i) const
	{
		return _rep->_allocator[i];
	};
	void write (int i, T c)
	{
	//	Construct a copy existing representation
		_rep=_rep->getOwnCopy();
	//	Substitute the i-th character in it
		_rep->_allocator[i]=c;
		return;
	}

public:	
	
	class BadString;

	DeferredString();
	DeferredString(const string&);
	DeferredString(const DeferredString&);
	DeferredString(const T*);
	~DeferredString();
	DeferredString& operator=( const DeferredString&);
	DeferredString& operator=( const T* );
	
	CharProxy operator[](int i)
	{
		check(i);
//	A proxy will be returned instead of a character
		return CharProxy(*this,i);
	}
	T operator[](int i) const
	{
		check(i);
	//	A character itself may be returned
		return _rep->_allocator[i];
	}
	int length()const
	{
		return _rep->_len;
	};
	void tester()const;
};


//String representation
template<class T>
struct DeferredString<T>::StringRep
{
//	pointer to the allocation og a string
	T* _allocator;
//	number of characters in the string
	size_t _len;		
//	how many oblects use this representation
	int _refCounter;
//	if the string may be sharable
	bool _shareable;

	StringRep (size_t, const T*);
	StringRep (size_t, const string&);
	~StringRep();
//	pseudo copy constructor
	StringRep* getOwnCopy()
	{
		//	A representation should be copied only
//	if it is shared
	if(_refCounter == 1)
		return this;
	_refCounter--;
	return new StringRep(_len,_allocator);
	}
//	pseudo assignment
	void assign (size_t, const T*);
	void makeShareable() {_shareable=true;}
	void makeUnshareable() {_shareable=false;}
	bool isShareable() const { return _shareable;}
private:
//	Wil never be implemented
	StringRep (const StringRep&);
	StringRep& operator= (const StringRep&);
};


//CharProxy 
template<class T>
class DeferredString<T>::CharProxy
{
	friend class DeferredString;
private:
//	String to which belongs proxy
	DeferredString & _proxyship;
//	Character substituted by a proxy
	int _index;
	CharProxy(DeferredString& ds, int i);

public:
	const T* operator&() const;
	T* operator&();
	operator T() const;
	operator T&();
	CharProxy& operator=(T c)
	{
		_proxyship.write(_index,c);
		return *this;
	}
};

//BadString
template<class T>
class DeferredString<T>::BadString
{
private:
	string _reason;
public:
	BadString(string reason):_reason(reason){};
	~BadString(){};
	void diagnose() const {cerr<<_reason<<endl;}
};

//=================END OF ANNOUNCEMENT===================


//implementation of DeferredString
template<class T>
DeferredString<T>::DeferredString()
	:_rep(new (nothrow)StringRep(0,""))
{
	checkForSpace();
#ifndef NDEBUG
	cout<<"DeferredString()"<<endl;
#endif
	return;
}

template<class T>
DeferredString<T>::DeferredString(const string& s)
	:_rep(new(nothrow) StringRep(s.length(),s))
{
	checkForSpace();
#ifndef NDEBUG
	cout<<"DeferredString(const string& s)"<<endl;
#endif
	return;
}

template<class T>
DeferredString<T>::DeferredString(const DeferredString<T>& d)
{
#ifndef NDEBUG
	cout<<"DeferredString<T>::DeferredString(const DeferredString<T>& d)"<<endl;
#endif

	if(d._rep->isShareable())
	{
		d._rep->_refCounter++;
		_rep = d._rep;
	}
	else
	{
		_rep = new(nothrow) StringRep(d._rep->_len,d._rep->_allocator);
		checkForSpace();
	}
	return;
}

template<class T>
DeferredString<T>::DeferredString(const T* ps)
	:_rep(ps == 0 ? throw BadString ("Attempt to use not defined pointer")
			:new(nothrow) StringRep(strlen(ps),ps))
{
#ifndef NDEBUG
	cout<<"DeferredString<T>::DeferredString(const T* ps)"<<endl;
#endif
	checkForSpace();
	return;
};

template<class T>
DeferredString<T>::~DeferredString()
{
		if (--_rep->_refCounter == 0) 
			delete _rep;
};

template<class T>	
DeferredString<T>& DeferredString<T>::operator=( const DeferredString<T>&ds)
{
//	protection from self assignment
	ds._rep->_refCounter++;
	assert ((&ds==this)?_rep->_refCounter>1:true);

	if (--_rep->_refCounter==0)
//	never occurs in the case of self assignment
		delete _rep;
	if (ds._rep->isShareable())
//	add this to a shared representation of ds
		_rep=ds._rep;
	else
//	create a new representation
		_rep=new (nothrow)StringRep(ds._rep->_len,ds._rep->_allocator);
	checkForSpace();
	return *this;		
};
template<class T>
DeferredString<T>& DeferredString<T>:: operator=( const T* ps )
{
	if (ps==0)
		throw BadString ("Attempt to use not defined pointer");
	if (_rep->_refCounter == 1)				
//	if nobody else uses this representation renew it
		_rep->assign(strlen(ps),ps);
	else
//	the representation is shared with others
	{
//		exclude itself from using it
		_rep->_refCounter--;
//		create a new representation
		_rep=new (nothrow) StringRep(strlen(ps),ps);
		checkForSpace();
	}
	return *this;
	}

//========END OF IMPLEMENTATION DEFERREDsTRING====================

//implementation of StringRep
template<class T>
DeferredString<T>::StringRep::StringRep(size_t len, const T* ps)
	:_len(len),
	_shareable(true),
	_refCounter(1),
	_allocator(new (nothrow)T[len+1])
{
#ifndef NDEBUG
	cout<<"DeferredString<T>::StringRep::StringRep(size_t len, const T* al)"<<endl;
#endif
	if (ps==0)
		throw BadString ("Attempt to use not defined pointer");
	if (_allocator == 0)
		throw BadString("No more space in the system");

	copyon(_allocator,ps);
	return;
}
template<class T>
DeferredString<T>::StringRep::StringRep (size_t len, const string& s)
	:_len(len),
	_shareable(true),
	_refCounter(1),
	_allocator(new (nothrow)T[len+1])
{
	if (_allocator == 0)
		throw BadString("No more space in the system");

	copychar(_allocator, s.c_str());
	return;
}
template<class T>
DeferredString<T>::StringRep::~StringRep()
{
	delete []_allocator;
}

//	pseudo assignment
template<class T>
void DeferredString<T>::StringRep:: assign (size_t len, const T* ps)
{
	if (ps==0)
		throw BadString ("Attempt to use not defined pointer");
	if (_len!=len)
	{
		delete [] _allocator;
		_len=len;
		_allocator = new(nothrow) char[_len+1];
		if(_allocator == 0)
			throw BadString("No more space in the system");
	}
	copyon(_allocator,ps);
	return;
}
//implementation charProxy
template<class T>
DeferredString<T>::CharProxy::CharProxy(DeferredString<T>& d,int i)
	:_proxyship(d), _index(i)
{
#ifndef NDEBUG
	cout<<"CharProxy constructor"<<endl;
#endif
	return;
}
template<class T>
const T* DeferredString<T>::CharProxy::operator&() const
{
	return &_proxyship._rep->_allocator[_index];
}

template<class T>
T* DeferredString<T>::CharProxy::operator&()
{

	if (_proxyship._rep->isShareable() && _proxyship._rep->_refCounter>1)
	{
		_proxyship._rep->_refCounter--;
		_proxyship._rep = new StringRep
				(_proxyship._rep->_len, _proxyship._rep->_allocator);
		if(_proxyship._rep == 0)
			throw BadString("No more space in the system");
	}
	_proxyship._rep->makeUnshareable();
	return &_proxyship._rep->_allocator[_index];
}
template<class T>
DeferredString<T>::CharProxy::operator T() const
{
	return _proxyship.read(_index);
}
template<class T>
DeferredString<T>::CharProxy::operator T&()
{
	if (_proxyship._rep->isShareable() && _proxyship._rep->_refCounter>1)
	{
		_proxyship._rep->_refCounter--;
		_proxyship._rep = new StringRep
				(_proxyship._rep->_len, _proxyship._rep->_allocator);
		if(_proxyship._rep == 0)
			throw BadString("No more space in the system");
	}
	_proxyship._rep->makeUnshareable();
	return _proxyship._rep->_allocator[_index];
}



template<class T>
ostream& operator<<(ostream& os, const DeferredString<T>&ds)
{
	for(size_t i = 0;i<ds.length();++i)
		os<<static_cast<T>(ds[i]);
	return os;
}

template <typename T>
void copychar(T* target, const char* source)
{
	T * t = target;
	const char * s = source;
	while (*t++ = *s++);
	return;
}

template <typename T>
void copyon(T* target, const T* source)
{
	T * t = target;
	const T * s = source;
	while (*t++ = *s++);
	return;
}


template<class T>
void DeferredString<T>::tester() const
{	
	cout<<*this<<endl;
	cout<<"Shareable: "<<boolalpha<<_rep->_shareable<<endl;;
	cout<<"RefCount : "<<_rep->_refCounter<<endl;
	cout<<"Represent: "<<_rep<<endl;
	return;
}

#endif