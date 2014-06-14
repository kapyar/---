// Основний компонент проекту опуклої оболонки точок площин
// складається з двох класів Polygon і Convex
//
// Клас Polygon забезпечує інтерфейс опуклої оболонки і
// двосторонньої черги, в якій зберігаються її точки
#pragma once
#ifndef _POLYGON_H_
#define _POLYGON_H_

#include "Segment.h"
#include"Geometry.h"
#include<deque>
#include<iostream>
using namespace std;


class Polygon
{
public:
	class BadInit;
	// Занести до многокутника перші три точки
	Polygon(const Point&,const  Point&,const Point&);
	~Polygon();
	// Долучити точку до многокутника
	void process(const Point&);
	// Обчислити і запам’ятати периметр
	double perimeter() const;
	// Обчислити і запам’ятати площу
	double area() const;
	void showPolygon();
private:
	// Вершини опуклої оболонки, збережені в двосторонній черзі
	std::deque <Point> _d;
	// Кількість вершин в опуклій оболонці
	int _edges;
	// Значення периметру
	double _perimeter;
	// Значення площі
	double _area;
	// Перевірити, чи знаходиться точка gjза стороноюs
	bool illuminated(const Segment&s, const Point& a) const;
	// Замінити сторону sдвома новими сторонами,
	// кінцями сторони sі точкою a
	void delEdge(const Segment& s, const Point& a);

	void deleteIlluminatedEdges(const Point &);
	void addNewEdges(const Point& p);

	
};

class Polygon::BadInit
{
private:
	string _reason;
public:
	BadInit(const string& s="unknown reason")
		:_reason(s)
	{

	}
	~BadInit()
	{
		return;
	}

	void diagnos()const
	{
		for(size_t i = 0;i<_reason.length();++i)
		{
			cout<<_reason[i]<<endl;
		}
	}

};

#endif
