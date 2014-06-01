#ifndef _DeferredString_h_
#define _DeferredString_h_

#include <string>
#include <iostream>
using namespace std;

class DeferredString;
void tester(const DeferredString&);

class DeferredString
{
	friend void tester(const DeferredString&);
private:
//	Representation of a shared string
	struct StringRep;
	StringRep* _rep;
//	Proxy class for a character in the string

public:	
	class CharProxy;
//	friend class CharProxy;

	class BadString;
	DeferredString();
	DeferredString(const string&);
	DeferredString(const DeferredString&);
	DeferredString(const char*);
	~DeferredString();
	DeferredString& operator=( const DeferredString&);
	DeferredString& operator=( const char* );
	void check(size_t i) const;
	char read(int i) const;
	void write (int i, char c);
	CharProxy operator[](int i);
	char operator[](int i) const;
	int length()const;
};

class DeferredString::CharProxy
{
	friend class DeferredString;
	friend ostream& operator<<(ostream&, const CharProxy&);
private:
//	String to which belongs proxy
	DeferredString & _proxyship;
//	Character substituted by a proxy
	int _index;
	CharProxy(DeferredString& ds, int i);

public:
	const char* operator&() const;
	char* operator&();
	operator char() const;
	operator char&();
	CharProxy& operator=(char c);
};

ostream& operator<<(ostream &, const DeferredString::CharProxy&);

class DeferredString::BadString
{
private:
	string _reason;
public:
	BadString(string reason):_reason(reason){};
	~BadString(){};
	void diagnose() const {cerr<<_reason<<endl;}
};

ostream& operator<<(ostream&, const DeferredString&);

#endif