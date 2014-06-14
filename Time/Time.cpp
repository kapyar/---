#include"Time.h"
#include<ctime>

const double Time::hourToDec = 1.0/3600;
//���������������� �������

Time Time::defaultTime=Time();
bool Time::defaultSet=false;

void Time::fillTime(int s, int m, int h)
{
// �� ����� ��������� ���� ���� ���, 
// ������� ������ ��������� �ᒺ���� �����
// defaultDate, ���� ���� ��������
// �� ������� ��������� ��������
   if(!defaultSet)
   {
      defaultSet=true;
      setDefault();
#ifndef NDEBUG
      cout<<"*Time constructor defaultTime: "<<*this<<endl;
#endif
// ���������� ���� �� ������������� � � ��������
      return;
   }
   if(h==-111)
	   _hours=defaultTime.getHours();
   else 
	   _hours=h;
   if(m==-111)
	   _minutes=defaultTime.getMinutes();
   else 
	   _minutes=m;
     if(s==-111)
		 _seconds=defaultTime.getSeconds();
   else 
	   _seconds=s;
   normalizeTime();
}

// ������ ���� �� ������������� ����������
void Time::setDefault(int s, int m, int h)
{
   defaultTime=Time(s, m, h);
}

void Time::setDefault()
{
// ��� ������� tm ����� � �������� ctime
// ��������� �������� �� ���������� ����
   struct tm* today=new tm;
// ������� ������� � ����������� ���������
   time_t timer;
   time(&timer);
   today=gmtime(&timer);
// ���� �������,�������,������
   defaultTime._hours=(today->tm_hour+2)%24;
   defaultTime._minutes=today->tm_min;
   defaultTime._seconds=today->tm_sec;

}
void Time:: showDefault()
{
	cout<<defaultTime;
}
Time::operator double() const
{
	return static_cast<int>(*this)*hourToDec;
}

double operator+(const Time& t1,const Time& t2)
{
	return static_cast<double>(t1)+static_cast<double>(t2);
}

Time::Time(int s, int m, int h)
{
	fillTime(s,m,h);
#ifndef NDEBUG
	cout<<"*Constructing Time"<<endl;
#endif
   normalizeTime();
   return;
}

// ����������� �����������
Time::Time(const Time& t):
   _seconds(t._seconds), 
   _minutes(t._minutes), 
   _hours(t._hours)
{
#ifndef NDEBUG
	cout<<"*Copy constructor Time"<<endl;
#endif
   return;
}
// �������� ���������
Time& Time::operator=(const Time& t)
{
#ifndef NDEBUG
	cout<<"*operator= Time"<<endl;
#endif
   _hours=t._hours;
   _minutes=t._minutes;
   _seconds=t._seconds;
   return *this;
}

// ������� ����������� ����
void Time::normalizeTime()
{//� ��� ������
	int tempTime=getHours()*3600+getMinutes()*60+getSeconds();
	if(tempTime<0) throw Time::BadTime(_seconds,_minutes,_hours);
	else
	{
		_hours=tempTime/3600;
		tempTime-=_hours*3600;
		_minutes=tempTime/60;
		_seconds=tempTime-_minutes*60;

	}
}
// ����������� �����
void Time::setHours(const int h)
{
   _hours=h;
   normalizeTime();
   return;
}
// ����������� ������
void Time::setMinutes(const int m)
{
   _minutes=m;
   normalizeTime();
   return;
}
// ����������� ������
void Time::setSeconds(const int s)
{
   _seconds=s;
   normalizeTime();
   return;
}

const Time& Time:: operator++()
{
	setSeconds(getSeconds()+1);
	return *this;
}
const Time Time:: operator++(int)
{
	const Time res(*this);
	++*this;
	return res;
}
const Time& Time:: operator--()
{
	setSeconds(getSeconds()-1);
	return *this;
}
const Time Time:: operator--(int)
{
	const Time res(*this);
	--*this;
	return res;
}