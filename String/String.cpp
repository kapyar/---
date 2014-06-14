#include <string>
#include "String.h"

String::String():
	_allocator(new char[1]),
	_len(0)
{
	_allocator[0]='\0';
#ifndef NDEBUG
	cout<<"Empty string "<<*this<<" created"<<endl;
#endif

	return;
}

String::String(const char c):
	_allocator(new char[2]),
	_len(1)
{
	_allocator[0]=c;
	_allocator[1]='\0';
	
#ifndef NDEBUG
	cout<<"One symbol string "<<*this<<" created"<<endl;
#endif

	return;
}

String::String(const string& s):
	_allocator( new char[s.length()+1]),
	_len(s.length())
{
	copyon(_allocator, s.c_str());
#ifndef NDEBUG
	cout<<"String from string"<<*this<<" created"<<endl;
#endif
	
	return;
}
//не можемо записати ініціалізацію зразу 
//виникає проблема при передачі нульового указника
String::String(const char* ps)
{
	if (ps==0)
		throw BadString("Attempt to use not defined pointer");
	_len=(strlen(ps));
	_allocator =(new char[_len+1]);
	copyon(_allocator, ps);
#ifndef NDEBUG
	cout<<"String from char* "<<*this<<" created"<<endl;
#endif
	return;
}

String:: String(const String & s, int multiplayer):
_len (multiplayer>0 ? s._len*multiplayer : s._len),
	_allocator ( new char[_len+1])
{
	char * target = _allocator;
	for (int i=0; i<multiplayer; i++)
	{
		copyon(target, s._allocator);
		target+=s._len;
	}
#ifndef NDEBUG
	cout<<"String "<<*this<<" copied"<<endl;
#endif
	return;
};

String::~String()
{
	delete [] _allocator;
	return;
}

String& String::operator=(const String& s)
{
	if (this==&s)
		return *this;
	delete [] _allocator;
	_len = s._len;
	_allocator = new char[_len+1];
	if(_allocator==0)
		throw BadString("No more space in the system");
	copyon(_allocator, s._allocator);
	return *this;
}

String& String::operator=(const string& s)
{
	delete [] _allocator;
	_len = s.length();
	_allocator = new char[_len+1];
	if(_allocator==0)
		throw BadString("No more space in the system");
	copyon(_allocator, s.c_str());
	return *this;
}

String& String::operator=(const char* ps)
{
	if (ps==0)
		throw BadString("Attempt to use not defined pointer");
	delete [] _allocator;
	_len=strlen(ps);
	_allocator = new char[_len+1];
	copyon(_allocator, ps);
	return *this;
}

String& String::operator=(const char c)
{
	delete [] _allocator;
	_len = 1;
	_allocator = new char[2];
	_allocator[0]=c;
	_allocator[1]='\0';
	return *this;
}

const string String::STL_string() const
{
	return string(_allocator);
}

char& String::operator[](size_t i)
{
	if((i<0)||(_len<=i))
		throw BadIndex(i);
	return _allocator[i];
};

const char String::operator[](size_t i) const
{
	if((i<0)||(_len<=i))
		throw BadIndex(i);
	return _allocator[i];
}

void copyon(char* target, const char* source)
{
	while(*target++=*source++);
	
	/*
	for (size_t i=0; i<len; ++i)
		target[i]=source[i];
	target[len]='\0';
	*/
	
}

String& String::operator+=(const String& s)
{
	size_t len = length()+s.length();
	char * newAllocator = new char[len+1];
	copyon(newAllocator, _allocator);
	copyon(newAllocator+_len, s._allocator);
	delete _allocator;
	_allocator = newAllocator;
	_len = len;
	return *this;
}

String& String::operator+=(const char* ps)
{
	if (ps==0)
		throw String::BadString("Attempt to use not defined pointer");
	size_t len=strlen(ps)+length();
	char * newAllocator = new char[len+1];
	copyon(newAllocator, _allocator);
	copyon(newAllocator+_len, ps);
	delete _allocator;
	_allocator = newAllocator;
	_len = len;
	return *this;
}

String& String::operator+=(const string& s)
{	
	//довжина нової стрічки
	size_t len = s.length()+length();
	char * newAllocator = new char[len+1];
	copyon(newAllocator, _allocator);
	copyon(newAllocator+_len, s.c_str());
	delete _allocator;
	_allocator = newAllocator;
	_len = len;
	return *this;
}

const String operator+(String s1, const String& s2)
{
	return s1+=s2;
}

bool operator==(const String& s1, const String& s2)
{
	bool equal = s1.length()==s2.length();
	for (size_t i=0; (i<s1.length())&&equal; i++)
		equal = s1[i]==s2[i];
	return equal;
}
bool operator!=(const String& s1, const String& s2)
{
	return !(s1==s2);
}
bool operator<(const String& s1, const String& s2)
{
	bool res = true;
	size_t i=0;
	while(res && (i<min(s1.length(),s2.length())))
	{
		res = res && (s1[i]==s2[i]);
		i++;
	}
	if (res)
		return s1.length()<s2.length();
	i--;
	return s1[i]<s2[i];
}

bool operator<=(const String& s1, const String& s2)
{
	if (s1==s2)
		return true;
	return s1<s2;
}
bool operator> (const String& s1, const String& s2)
{
	return !(s1<=s2);
}
bool operator>= (const String& s1, const String& s2)
{
	return !(s1<s2);
}