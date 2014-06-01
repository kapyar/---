#include "Convex.h"

Convex::Convex()
	:_angles(zero), _a(0,0), _b(0,0),_pm(0)
{
	return;
}
Convex::~Convex()
{
	if(_angles == many)
		delete _pm;
}
// Долучити чергову точку
Convex& Convex::add(const Point& p )
{
	switch(_angles)
	{
	default: break;
	case zero:
		process0(p);
		break;
	case one:
		process1(p);
		break;
	case two:
		process2(p);
		break;
	case many:
		processN(p);
		break;
	}
	return *this;
}
// Залежно від кількості точок в оболонці
// (одна, дві або більше) обчислити периметр або
// звернутися до периметра многутника
double Convex::perimeter() const
{
	if(_angles == many)
	{
		return _pm->perimeter();
	}else if(_angles == two)
	{
		return 2* distanceBetweenPoints(_a,_b);
	}
	return 0;
}
// Те ж саме з площею
double Convex::area() const
{
	if(_angles == many)
	{
		return _pm->area();
	}
	else
	{
		return 0;
	}
}


// Обробити першу точку
void Convex::process0(const Point& p )
{
	_a = p;
	_angles = one;
	return;
}
// Обробити другу точку
void Convex::process1(const Point& p)
{
	_b = p;
	_angles = two;
	return;
}
// Обробити третю точку
void Convex::process2(const Point& p )
{
	if(!isPointsOnTheSameLine(_a,_b,p))
	{
		_pm = new Polygon(_a,_b,p);
		_angles = many;
	}else 
	{
		Segment ap(_a,p), bp(_b,p), ab(_a,_b);
		if (isPointsOnTheSameLine(p, _a, _b)) {
		}
		else if (isPointsOnTheSameLine(_b, _a, p))
			_b = p;
		else if (isPointsOnTheSameLine(_a, p, _b))
			_a = p;

	}
	return;
}
// Обробити наступну після третьої точки
void Convex::processN(const Point& p )
{
	_pm->process(p);
	return;
}

void Convex::show()
{
	switch(_angles)
	{
	case zero:
		cout<<"It is no side to show"<<endl;
		break;
	case one:
		cout<<_a<<endl;
		break;
	case two:
		cout<<_a<<' '<<_b<<endl;
		break;
	case many:
		_pm->showPolygon();
		break;
	default:
		throw Polygon::BadInit("Why am I here");

	}
}