#include"Date.h"

//Визначаємо статичні атрибути та методи класу
Date Date::defaultDate=Date();
 
bool Date::defaultSet=false;

//повертає кількість днів у місці у поточній даті
int Date:: numberOfDaysInMonth(int month)
{
	int numberOfDays= 0;
	 switch(month)
   {
// У лютому враховуємо високосний рік
   case feb:
	   numberOfDays=28+leapYear(year());
      break;
   case apr: case jun: case sep: case nov:
      numberOfDays=30;
      break;
   case jan: case mar: case may:
   case jul: case aug: case oct: case dec:
      numberOfDays=31;
      break;
// Місяць виявився некоректним
   default:
      throw BadDate(_day, _month, _year);
   }
	 return numberOfDays;
}

 void Date::fillDate(int d, Month m, int y) 
{
// Ця умова спрацьовує рівно один раз, 
// оскільки першим створеним об’єктом стане
// defaultDate, який буде створено
// до початку виконання програми
   if(!defaultSet)
   {
      defaultSet=true;
      setDefault();
#ifndef NDEBUG
      cout<<"Data constructor defaultDate: "<<*this<<endl;
#endif
// Встановили дату за замовчуванням — і виходимо
      return;
   }
// Тепер аналізуємо параметри:
// неіснуючі (вони нульові) беремо 
// з дати за замовчуванням,
// яка вже гарантовано була визначена
   _day=d? d :defaultDate._day;
   _month=m? m :defaultDate._month;
   _year=y? y: defaultDate._year;

// Готуємося визначити кількість днів у місяці
// 28, 29, 30 чи 31 
   int numberOfDays = numberOfDaysInMonth(_month);
// Перевірка коректності дня і року
   if((_day<1)||(numberOfDays<_day)||(_year<0))
      throw BadDate(_day, _month, _year);
#ifndef NDEBUG
   cout<<"Data constructor: "<<*this<<endl;
#endif
};

//проініцалізуємо статичні атрибути класу
string Date::monthNames[12] =
{
	"Jan", "Feb", "Mar", "Apr", "May", "Jun", 
   "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};

// Задати дату за замовчуванням параметром
void Date::setDefault(int d, Month m, int y)
{
   defaultDate=Date(d, m, y);
}

void Date::setDefault()
{
// Тип таймера tm взято з бібліотеки ctime
// Створення указника на сьогоднішній день
   struct tm* today=new tm;
// Обробка таймера й ініціалізація сьогоднішнього дня
   time_t timer;
   time(&timer);
   today=gmtime(&timer);
// Вибір дня, місяця і року
   defaultDate._day=today->tm_mday;
   defaultDate._month=++(today->tm_mon);
   defaultDate._year=today->tm_year+=1900;
}

void Date::showDefault()
{
   cout<<defaultDate;
}

/////************************////////////////
//визначення високосного року
//http://uk.wikipedia.org/wiki/%D0%92%D0%B8%D1%81%D0%BE%D0%BA%D0%BE%D1%81%D0%BD%D0%B8%D0%B9_%D1%80%D1%96%D0%BA
bool Date::leapYear(int y)
{
	if((y%4==0) && ((y%100!=0 || y%400 == 0)) )
		return true;
	return false;
}

Date::Date ( int d, Month m, int y)
{
   fillDate(d, m, y);
   #ifndef NDEBUG
		cout<<"*Constructing Date with default"<<endl;
#endif
}

Date::Date(int d, int m, int y)
{
   fillDate(d, Month(m), y);
#ifndef NDEBUG
		cout<<"*Constructing Date without default"<<endl;
#endif
}

Date::Date (const Date&  a)
	: _day(a.day()), _month(a.month()), _year(a.year())
{
#ifndef NDEBUG
		cout<<"*Copy Constructor Date"<<endl;
#endif
}

/*------------------*/
//модифікатори
void Date::setDay(int d)
{

	if(d<1 ||d>numberOfDaysInMonth(_month)) 
	{
		cerr<<"Invalid day: "<<d<<endl;
		throw Date::BadDate(d,_month,_year);
	}
	else _day=d;
	
}
void Date::setMonth(int m)
{
	if(m<1 ||m>12) 
	{
		cerr<<"Invalid month: "<<m<<endl;
		throw Date::BadDate(_day,m,_year);
	}
	else _month=m;
}
void Date::setDYear(int y)
{
	if(y<0) 
	{
		cerr<<"Only A.C"<<endl;
		throw Date::BadDate(_day,_month,y);
	}
	else _year=y;
}


//інкременти та дикриментиоператори
const Date& Date::operator++()
{
	if(_day+1>numberOfDaysInMonth(_month))
	{
		_day=1;
		if(_month+1>12)
		{
			_month=1;
			++_year;

		}
		else ++_month;
	}
	else ++_day;
	return *this;
}
const Date Date::operator++(int)
{
	Date temp(*this);
	++*this;
	return temp;
}

const Date& Date::operator--()
{
if(_day-1<1)
	{
		if(_month-1<1)
		{
			--_year;
			_month=12;
			_day=31;//грудень
		}
		else
		{
			--_month;
			_day=numberOfDaysInMonth(_month);
		}
		
}
else --_day;
	return *this;
}
const Date  Date::operator--(int)
{
	Date temp(*this);
	--*this;
	return temp;
}
