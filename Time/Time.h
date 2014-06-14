#include<iostream>
using namespace std;

class Time
{
private:
	int _hours;
	int _minutes;
	int _seconds;
//������� ��������, � ���� �������
	void normalizeTime();
	void fillTime(int s, int m, int h);
	static bool defaultSet;
	static Time defaultTime;
public:
	struct BadTime;
	static const double hourToDec;
	//-111 ��� ���� ��� ���������� ��� �� 
	//������������� ���� �������, �������
	//�� ������ ���������� �� -111 �� ��� ��������
	//��������� � ��������� ���������
	//�������� ���� ��������� ����� � ������ ����� ����
	//���������� ����� -111 
	Time (int s=-111, int m=-111, int h=-111);
	Time (const Time&);
	~Time(){};
	Time& operator=(const Time&);
	operator int() const;
	operator double() const;

	static void setDefault(int s, int m, int h);
	static void setDefault();
	static void showDefault();

//���������
	int getHours() const {return _hours;}
	int getMinutes() const {return _minutes;}
	int getSeconds() const {return _seconds;}
//������������
	void setHours(const int);
	void setMinutes(const int);
	void setSeconds(const int); 
//���� �������� ������� �� ���� �������
	const Time& operator++();
	const Time operator++(int);
	const Time& operator--();
	const Time operator--(int);
};

double operator+(const Time& t1,const Time& t2);

struct Time::BadTime
{
	int _s, _m, _h;
	BadTime(int s, int m, int h):_s(s), _m(m), _h(h)
	{
#ifndef NDEBUG
		cout<<"*Constructing BadTime"<<endl;
#endif
	}
	BadTime(const Time& b)
		:_h(b.getHours()),_m(b.getHours()),_s(b.getMinutes())
	{
#ifndef NDEBUG
		cout<<"*Copy constructor BadTime"<<endl;
#endif
	}
};
inline ostream& operator<<(ostream& os,const Time::BadTime& bt)
{
	os<<bt._h<<"h ";
	os<<bt._m<<"m ";
	os<<bt._s<<"s ";
	return os;

}

inline Time::operator int() const
{
	return getHours()*3600+getMinutes()*60+getSeconds();
}

inline ostream& operator<<(ostream& os, const Time & t)
{
	os<<t.getHours()<<"h ";
	os<<t.getMinutes()<<"m ";
	os<<t.getSeconds()<<"s ";
	return os;

}
