//******************************************
//Every segment posesses its unique ID.
//In debug mode both constructor and destructor
//report the ID and the coordinates
//of a segment created or resp. deleted

//Developed by Yaroslav Kaplunskiy
//at 07.02.2013
//Version 1.0

//*******************************************
// Клас відрізків

#pragma once
#ifndef _SEGMENT_H_
#define _SEGMENT_H_
#include<cassert>
#include"Point.h"
#include<cmath>
#define NDEBUG

class Segment;
const double utDistance( const Point& a,const Point& b);

class Segment

{

private:
	Point _a;// Точка початку відрізку
	Point _b;// Точка кінця відрізку

public:
	// Конструктори відрізків
	Segment(const double x1=0, const double y1=0,
		const double x2=1, const double y2=0):
	_a(x1,y1),_b(x2,y2)
	{

	}

	Segment(const Point &start, const Point &end):
		_a(start),_b(end)
	{

	}

	Segment(const Segment& s):
		_a(s.start()),_b(s.end())
	{

	}

	~Segment()
	{

	}

	Segment& operator=(const Segment&s)
	{
		_a=s.start();
		_b=s.end();
		return *this;
	}

	//Селектори
	const Point& Segment::start() const
	{
		return _a;
	}

	const Point& Segment::end() const
	{
		return _b;
	}

	// Селектори-модифікатори точок
	Point &Segment::start()
	{
		return _a;
	}
	Point &Segment::end()
	{
		return _b;
	}

	// Селектори координат точок
	const double &Segment::startX() const
	{
		return _a.getX();
	}

	const double &Segment::startY() const
	{
		return _a.getY();
	}

	const double &Segment::endX() const
	{
		return _b.getX();
	}

	const double &Segment::endY() const
	{
		return _b.getY();
	}

	const double &Segment::getStartX() const
	{
		return _a.getX();
	}
	const double &Segment::getStartY() const
	{
		return _a.getY();
	}
	const double &Segment::getEndX() const
	{
		return _b.getX();
	}
	const double &Segment::getEndY() const
	{
		return _b.getY();
	}


	// Селектори-модифікатори координат точок

	double &Segment::startX()
	{
		return _a.x();
	}

	double &Segment::startY()
	{
		return _a.y();
	}

	double &Segment::endX()
	{
		return _b.x();
	}

	double &Segment::endY()
	{
		return _b.y();
	}

	void Segment::setStartX(const double & i) 
	{
		_a.setX(i);
	}
	void Segment::setStartY(const double & i) 
	{
		_a.setY( i);

	}
	void Segment::setEndX(const double& i) 
	{

		_b.setX(i);
	}
	void Segment::setEndY(const double & i) 
	{
		_b.setY(   i);
	}
	// Обчислення довжини відрізка
	double length () const
	{
		return sqrt((_a.x()-_b.x())*(_a.x()-_b.x())
			+(_a.y()-_b.y())*(_a.y()-_b.y()));
	}


	double Segment::distance (const Point&c) const
	{
		double cosA((utDistance(_a,c)*utDistance(_a,c)+
			this->length()*this->length()-utDistance(_b,c)*utDistance(_b,c))/2*utDistance(_a,c)*this->length());

		double cosB((utDistance(_b,c)*utDistance(_b,c)+
			this->length()*this->length()-utDistance(_a,c)*utDistance(_a,c))/2*utDistance(_b,c)*this->length());


		if (cosA<0)
		{
#ifndef NDEBUG
			cout<<"It is not a perpendicular"<<endl;
#endif
			return utDistance(_a,c);
		}
		else if(cosB<0)
		{
#ifndef NDEBUG
			cout<<"It is not a perpendicular"<<endl;
#endif
			return utDistance(_b,c);  
		}
		else
		{
#ifndef NDEBUG
			cout<<"It is  a perpendicular"<<endl;
#endif
			// Перевірка паралельності осі ординат
			double A=(_a.x()==_b.x()? 0 :(1/(_b.x()-_a.x())));
			// Перевірка паралельності осі абсцис
			double B=(_b.y()==_a.y()? 0 :1/(_a.y()-_b.y()));
			double C=-_a.x()*A - _a.y()*B;
			assert((A!=0)||(B!=0));
			if(B==0)
				return fabs(-C/A-c.y());
			if(A==0)
				return fabs(-C/B-c.x());
			return fabs((A*c.x()+B*c.y()+C)/sqrt(A*A+B*B));
		}
	}

};
inline ostream& operator<<(ostream &os, const Segment &s)
{
	os<<"\tstarts in: ("<<s.start()<<"\n\tfinish in: ("<<s.end()<<')'<<endl;
	os<<"\tlenght :"<<s.length();
	return os;
}


inline const double utDistance( const Point& a,const Point& b)
{
	return sqrt((a.x()-b.x())*(a.x()-b.x())
		+(a.y()-b.y())*(a.y()-b.y()));
}
#endif