
#ifndef _DATE_H_
#define _DATE_H_

#include<iostream>
using namespace std;
#include <ctime>

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


private:
	int _day, _month, _year;
	bool leapYear(int y);
	void fillDate(int d, Month m, int y);
	int numberOfDaysInMonth(int);
	static string monthNames [12];
	static bool defaultSet;
	static Date defaultDate;
};

inline bool operator<(const Date& a, const Date& b)
{
 if (a.year()<b.year()) return true;
 if (a.year()>b.year()) return false;
 if (a.month()<b.month()) return true;
 if (a.month()>b.month()) return false;
 if (a.day()<b.day())return true;
 return false;
}
inline bool operator>(const Date& a, const Date& b)
{
	return!(a<b);
}
inline bool operator==(const Date& a, const Date& b)
{
	return (a.day()==b.day()&& a.month()==b.month()&& a.year()==b.year());
}
inline bool operator>=(const Date& a, const Date& b)
{
	return(a>b || a==b);
}

inline bool operator<=(const Date& a, const Date& b)
{
	return(a<b || a==b);
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
};

inline ostream& operator<<(ostream& os, const Date::BadDate & bd)
{
	os<<"**Bad Date: "<<bd._day<<". "<<bd._month<<". "<<bd._year<<endl;
	return os;
}

#endif