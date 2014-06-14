#ifndef _DATE_H_
#define _DATE_H_

#include<iostream>
#include <ctime>
using namespace std;

//#define NDEBUG

class Date
{
public:
struct BadDate;
// to avoid problem 7.2.2002 7 feb or jul 2?
enum Month {jan=1, feb, mar, apr, may, jun, jul, aug, sep, oct, nov, dec};

//конструктор з параметрами за замовчуванням
Date ( int d=0, Month m=Month(0), int y=0);
//конструктор з обовязково заданими полями
Date(int d, int m, int y);
//копіювальний0
Date (const Date& );	
~Date()
{
#ifndef NDEBUG
		cout<<"Destructor Date"<<endl;
#endif
}

Date operator=(const Date& d)
{
	_day = d.day();
	_month = d.month();
	_year = d.year();

	return*this;
}
//селектори
int day() const{return _day;};
Month month() const{return Month(_month);};
int year() const{return _year;};

const string getMonthName() const{return monthNames[month()-1];};//-1 бо monthNames [12] 0=1

//модифікатори
void setDay(int d);
void setMonth(int);
void setDYear(int);

static void setDefault(int,Month,int);
static void setDefault();
static void showDefault();

//інкрементні та дикриментні оператори
const Date& operator++();
const Date  operator++(int);
const Date& operator--();
const Date  operator--(int);

time_t toSeconds()const;

private:
	int _day, _month, _year;
	bool leapYear(const int y)const;
	const int howManyLeaps(const int year)const;
	const int howManyDaysToMounth(const int m)const;
	const int howManyDaysInDate()const;
	void fillDate(int d, Month m, int y);
	const int numberOfDaysInMonth(const int)const;
	static string monthNames [12];
	static bool defaultSet;
	static Date defaultDate;
};

inline bool operator==(const Date& d1, const Date& d2)
{
	if(d1.day()!=d2.day())return false;
	else if(d1.month()!=d2.month())return false;
	else if(d1.year()!=d2.year())return false;
	
	else return true;
}

inline bool operator!=(const Date& d1, const Date& d2)
{
	return !(d1==d2);
}

inline ostream& operator<<(ostream& os, const Date & d)
{
	os<<d.day()<<' ';
	for(size_t i = 0;i<d.getMonthName().length();++i)
		os<<d.getMonthName()[i];
	os<<' '<<d.year();
	return os;
}

struct Date::BadDate
{
	int _day, _month, _year;
	BadDate(int d, int m, int y):_day(d), _month(m), _year(y)
	{
#ifndef NDEBUG
		cout<<"Constructing BadDate"<<endl;
#endif
	};
	BadDate(const Date& b)
		:_day(b.day()),_month(b.month()),_year(b.year())
	{
#ifndef NDEBUG
		cout<<"*Copy constructor BadDate"<<endl;
#endif
	}
};

inline ostream& operator<<(ostream& os, const Date::BadDate & bd)
{
	os<<"**Bad Date: "<<bd._day<<". "<<bd._month<<". "<<bd._year<<endl;
	return os;
}

#endif