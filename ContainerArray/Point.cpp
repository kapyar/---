#include<iostream>
using namespace std;
#include "Point.h"


//����������� ��������� ������
 int Point::_freeID(0);
 


 //����������� ���������
Point::	Point (const Point & a):
		_x(a.getX()),_y(a.getY()),_pointID(++_freeID)
{	
	#ifndef NDEBUG
		cout<<*this<<" was copied  "<<endl;
	#endif
	return;
};

Point::~Point()
{
	#ifndef NDEBUG
		cout<<*this<<" was removed  "<<endl;
	#endif
	//�� �������� _freeID ������� ����� ���� �� ��� 
	//��������� ����� � ���������� ����� ���������� 
	//� ���� ���� ��������� --_freeID
	return;
}

Point& Point::operator=(const Point & a)
{
//1. �������� ������ ��'���
	if (this==&a)
		return *this;
//�������� �������� 
	this->setX(a.getX());
	this->setY(a.getY());
	return *this;
}

ostream& operator<<(ostream& os, const Point& a)
{
	os<<"Point � "<<a.getID()<<": (x="<<a.getX()<<" y="<<a.getY()<<')';
	return os;
}

const Point operator+ (const Point & u, const Point & v)
{
#ifndef NDEBUG
	cout<<"In operator+"<<endl;
#endif
	return Point(u.getX()+v.getX(),u.getY()+v.getY());
	
}

Point& operator+=(Point & a, const Point& b)
{
	#ifndef NDEBUG
		cout<<"In operator+="<<endl;
	#endif
	a.setX(a.getX()+b.getX());
	a.setY(a.getY()+b.getY());
	return a;
}

bool operator==(const Point & u, const Point &v)
{
	#ifndef NDEBUG
		cout<<"In operator=="<<endl;
	#endif
	if(u.getX()!=v.getX()) 
		return false;
	else 
	{
		if(u.getY()!=v.getY())
			return false;
		else 
			return true;
	}	
}

bool operator!=(const Point & u, const Point &v)
{	
	#ifndef NDEBUG
		cout<<"In operator!="<<endl;
	#endif
	return !(u==v);
}
