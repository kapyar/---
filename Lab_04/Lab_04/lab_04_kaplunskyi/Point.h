#include<iostream>
using namespace std;

#pragma once
#ifndef _POINT_H_
#define _POINT_H_
#define NDEBUG
class Point
{
private:
	double _x;
	double _y;

public:
	//конструктор inline
	Point (double x=0, double y=0):
		_x(x),_y(y)
	{
#ifndef NDEBUG
		cout<<"Point :  (x="<<_x<<" y="<<_y<<") was created"<<endl;
#endif
		//оскільки об'єкти створюються тільки в конструкторах 
		//то перемінна _amount буде рахувати кількість 
		//створених обєктів за час існування програми
	};

	//конструктор копіювання
	//конструктор копіювання
	Point::	Point (const Point & a):
		_x(a.getX()),_y(a.getY())
	{	

		return;
	};
	Point::~Point()
{
	return;
}
	Point& Point::operator=(const Point & a)
{
//1. Видалити старий об'єкт
	if (this==&a)
		return *this;
//присвоїти значення 
	this->setX(a.getX());
	this->setY(a.getY());
	return *this;
}

	//модифікатори
	double& x(){return _x;};
	double& y(){return _y;};
	void setX(double x){_x=x;};
	void setY(double y){_y=y;};

	//селектори
	const double& x() const {return _x;};
	const double& y() const {return _y;};
	const double& getX() const {return _x;};
	const double& getY() const {return _y;};

};

//не члени класу
inline ostream& operator<<(ostream& os, const Point& a)
{
	os<<"Point # : (x="<<a.getX()<<" y="<<a.getY()<<')';
	return os;
}
inline const Point operator+ (const Point & u, const Point & v)
{
#ifndef NDEBUG
	cout<<"In operator+"<<endl;
#endif
	return Point(u.getX()+v.getX(),u.getY()+v.getY());
	
}
inline Point& operator+=(Point & a, const Point& b)
{
	#ifndef NDEBUG
		cout<<"In operator+="<<endl;
	#endif

	a.setX(a.getX()+b.getX());
	a.setY(a.getY()+b.getY());
	return a;
}
inline bool operator==(const Point & u, const Point &v)
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
inline bool operator!=(const Point & u, const Point &v)
{	
	#ifndef NDEBUG
		cout<<"In operator!="<<endl;
	#endif
	return !(u==v);
}
#endif