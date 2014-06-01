#pragma once
#ifndef _CONVEX_H_
#define _CONVEX_H_

#include"Polygon.h"

// ������������ ���� ������ ��������
class Convex
{
public:
	Convex();
	~Convex();
	// �������� ������� �����
	Convex& add(const Point&);
	// ������� �� ������� ����� � ��������
	// (����, �� ��� �����) ��������� �������� ���
	// ���������� �� ��������� ����������
	double perimeter() const;
	// �� � ���� � ������
	double area() const;
	void show();
private:
	// �������������� ������� ����� � ��������:
	// �����, ����, �� ��� ����� ����
	enum Angles {zero, one, two, many};
	Angles _angles;
	// ����� �� ����� ��������
	Point _a, _b;
	// ����������� (������� ����� �������� ����� ����)
	Polygon * _pm;
	// �������� ����� �����
	void process0(const Point&);
	// �������� ����� �����
	void process1(const Point&);
	// �������� ����� �����
	void process2(const Point&);
	// �������� �������� ���� ������ �����
	void processN(const Point&);

};

#endif