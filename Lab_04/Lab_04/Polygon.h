// �������� ��������� ������� ������ �������� ����� ������
// ���������� � ���� ����� Polygon � Convex
//
// ���� Polygon ��������� ��������� ������ �������� �
// ������������ �����, � ��� ����������� �� �����
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
	// ������� �� ������������ ����� ��� �����
	Polygon(const Point&,const  Point&,const Point&);
	~Polygon();
	// �������� ����� �� ������������
	void process(const Point&);
	// ��������� � ���������� ��������
	double perimeter() const;
	// ��������� � ���������� �����
	double area() const;
	void showPolygon();
private:
	// ������� ������ ��������, �������� � ����������� ����
	std::deque <Point> _d;
	// ʳ������ ������ � ������ ��������
	int _edges;
	// �������� ���������
	double _perimeter;
	// �������� �����
	double _area;
	// ���������, �� ����������� ����� gj�� ��������s
	bool illuminated(const Segment&s, const Point& a) const;
	// ������� ������� s����� ������ ���������,
	// ������ ������� s� ������ a
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
