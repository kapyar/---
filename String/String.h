#ifndef _string_h_ 
#define _string_h_

//Доповнити наведену нижче специфікаію до власного класу рядків String,
//забезпечивши можливість виконання змішаних операцій
//над власними рядками, С-рядками і STL-рядками
#include<string>
#include<iostream>
using namespace std;

class String
{
private:
	size_t _len;
	char* _allocator;

public:
	class BadString;
	class BadIndex;

	String();
	explicit String(const char*);
	String(const char);
	explicit String(const string&);
	String(const String & s, int multiplayer = 1);
	
	~String();

	String& operator=(const String&);
	String& operator=(const string&);
	String& operator=(const char*);
	String& operator=(const char);
	
	const string STL_string() const;
	const char* c_str() const{return _allocator;}
	
	size_t length() const{return _len;}
	bool empty() const{return _len==0;}
	void clear(){*this=String();}
	
	char& operator[](size_t);
	const char operator[](size_t) const;

	String& operator+=(const char*);
	String& operator+=(const String&);
	String& operator+=(const string&);
};
//зробили утилітами для того, оператор можна було викликати як зліва так і
//справа від об'єкта, також для майбутніх порівнянь коли буде використовуватись
//зведення типів
	bool operator==(const String& s1,const String& s2);
	bool operator!=(const String& s1,const String& s2);
	bool operator< (const String& s1,const String& s2);
	bool operator<=(const String& s1,const String& s2);
	bool operator> (const String& s1,const String& s2);
	bool operator>=(const String& s1,const String& s2);

	const String operator+(String s1, const String& s2) ;
	
	//копіювання стрічки
	void copyon(char* target, const char* source);

inline ostream& operator<<(ostream& os, const String& s)
{
	for(size_t i=0; i<s.length(); i++)
		os<<s[i];
	return os;
}

class String::BadString
{
private:
	string _reason;

public:
	BadString(string reason=""):
		_reason(reason)
	{
		return;
	};
	~BadString()
	{
		return;
	};
	string reason() const 
	{
		return _reason;
	}
};

//виведення String::BadString
inline ostream & operator<<(ostream& os, const String::BadString& s )
{
	os<<s.reason();
	return os;
}

class String::BadIndex
{
private:
	int _index;
public:
	BadIndex(const int i):_index(i)
	{
#ifndef NDEBUG
	cout<<"*Construct BadIndex"<<endl;
#endif
	}
	int getIndex()const{return _index;}
};
inline ostream & operator<<(ostream& os, const String::BadIndex& s )
{
	os<<s.getIndex();
	return os;
}

#endif