#include "DeferredString.h"
#include <cassert>
#include <iostream>
using namespace std;

struct DeferredString::StringRep
{
//	pointer to the allocation on a string
	char* _allocator;
//	number of characters in the string
	size_t _len;		
//	how many objects use this representation
	int _refCounter;
//	if the string may be sharable
	bool _shareable;

	StringRep (size_t, const char*);
	StringRep (size_t, const string&);
	~StringRep();
//	pseudo copy constructor
	StringRep* getOwnCopy();
//	pseudo assignment
	void assign (size_t, const char*);
	void makeShareable() {_shareable=true;}
	void makeUnshareable() {_shareable=false;}
	bool isShareable() const { return _shareable;}
private:
//	Wil never be implemented
	StringRep (const StringRep&);
	StringRep& operator= (const StringRep&);
};

DeferredString::DeferredString():
	_rep (new StringRep(0,""))
{
	if(_rep == 0)
		throw BadString("No more space in the system");	
	return;
}
DeferredString::DeferredString(const string& s):
	_rep (new StringRep(s.length(), s))
{
	if(_rep == 0)
		throw BadString("No more space in the system");	
	return;
}

DeferredString::DeferredString(const DeferredString& ds)
{
	if (ds._rep->isShareable())
//	this representation will be shared
//	with those of ds
	{
		ds._rep->_refCounter++;
		_rep=ds._rep;
	}
	else
//	create a new representation
		_rep=new StringRep(ds._rep->_len,ds._rep->_allocator);
	return;
}

DeferredString::DeferredString(const char* ps)
{
	if (ps==0)
		throw BadString ("Attempt to use not defined pointer");
	_rep=new StringRep(strlen(ps),ps);
	if(_rep == 0)
		throw BadString("No more space in the system");	
	return;
}

DeferredString::~DeferredString()
{
	if (--_rep->_refCounter==0) delete _rep;
	return;
}

DeferredString& DeferredString::operator=(const DeferredString &ds)
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
		_rep=new StringRep(ds._rep->_len,ds._rep->_allocator);
	return *this;
}

DeferredString& DeferredString::operator=(const char* ps)
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
		_rep=new StringRep(strlen(ps),ps);
	}
	return *this;
}

void DeferredString::check(size_t i) const
{
//	check if the index is within of the range
	if (i<0||_rep->_len<=i)
	{
		throw BadString("Bad Index");
	}
	return;
}

char DeferredString::read(int i) const
{
	return _rep->_allocator[i];
}

void DeferredString::write (int i, char c)
{
//	Construct a copy existing representation
	_rep=_rep->getOwnCopy();
//	Substitute the i-th character in it
	_rep->_allocator[i]=c;
	return;
}

DeferredString::CharProxy DeferredString::operator[](int i)
{
	check(i);
//	A proxy will be returned instead of a character
	return CharProxy(*this,i);
}

char DeferredString::operator[](int i) const
{
	check(i);
//	A character itself may be returned
	return _rep->_allocator[i];
}

int DeferredString::length()const
{
	return _rep->_len;
}

DeferredString::StringRep::StringRep (size_t len, const string& s):
	_shareable (true),
	_refCounter (1),
	_len(len),
	_allocator(new char[len+1])
//	DeferredString + \0
{
	if (_allocator == 0)
		throw BadString("No more space in the system");

	strcpy(_allocator, s.c_str());
	return;
}

DeferredString::StringRep::StringRep (size_t len, const char* ps):
	_shareable (true),
	_refCounter (1),
	_len(len),
	_allocator(new char[len+1])
//	DeferredString + \0
{
	if (ps==0)
		throw BadString ("Attempt to use not defined pointer");
	if (_allocator == 0)
		throw BadString("No more space in the system");

	strcpy(_allocator,ps);
	return;
}

DeferredString::StringRep::~StringRep()
{
	delete [] _allocator;
}

DeferredString::StringRep* DeferredString::StringRep::getOwnCopy()
{
//	A representation should be copied only
//	if it is shared
	if(_refCounter==1)
		return this;
	_refCounter--;
	return new StringRep(_len,_allocator);
}

void DeferredString::StringRep::assign (size_t len, const char* ps)
{
	if (ps==0)
		throw BadString ("Attempt to use not defined pointer");
	if (_len!=len)
	{
		delete [] _allocator;
		_len=len;
		_allocator = new char[_len+1];
	}
	strcpy(_allocator,ps);
	return;
}

DeferredString::CharProxy::CharProxy(DeferredString& ds, int i):
		_proxyship(ds), _index(i)
{
	return ;
}

const char* DeferredString::CharProxy::operator&() const
{
	return &_proxyship._rep->_allocator[_index];
}

char* DeferredString::CharProxy::operator&()
{
	if (_proxyship._rep->isShareable() && _proxyship._rep->_refCounter>1)
	{
		_proxyship._rep->_refCounter--;
		_proxyship._rep = new StringRep
				(_proxyship._rep->_len, _proxyship._rep->_allocator);
	}
	_proxyship._rep->makeUnshareable();
	return &_proxyship._rep->_allocator[_index];
}

DeferredString::CharProxy::operator char() const
{
	return _proxyship.read(_index);
}

DeferredString::CharProxy::operator char&()
{
	if (_proxyship._rep->isShareable() && _proxyship._rep->_refCounter>1)
	{
		_proxyship._rep->_refCounter--;
		_proxyship._rep = new StringRep
				(_proxyship._rep->_len, _proxyship._rep->_allocator);
	}
	_proxyship._rep->makeUnshareable();
	return _proxyship._rep->_allocator[_index];
}

DeferredString::CharProxy& DeferredString::CharProxy::operator=(char c)
{
	_proxyship.write(_index,c);
	return *this;
}

ostream& operator<<
		(ostream & os, const DeferredString::CharProxy& charp)
{
	os<<static_cast<char>(charp);
	return os;
}

void tester(const DeferredString& ds)
{
	cout<<ds<<endl;
	cout<<"Shareable: "<<boolalpha<<ds._rep->_shareable<<endl;
	cout<<"RefCount : "<<ds._rep->_refCounter<<endl;
	cout<<"Represent: "<<ds._rep<<endl;
	return;
}

ostream& operator<<(ostream& os, const DeferredString& s)
{
	for(int i=0; i<s.length(); i++)
		os<<static_cast<char>(s[i]);
	return os;
}
