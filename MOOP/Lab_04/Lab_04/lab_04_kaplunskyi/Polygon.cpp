# include"Polygon.h"
#include"Point.h"


Polygon::Polygon(const Point& a,const Point& b,const Point& c)
	:_edges(0),_perimeter(0),_area(0)
{
	if(isPointsOnTheSameLine(a,b,c))
	{
		throw BadInit("three points on the same line");
	}
	_d.push_front(b);
	if(illuminated(Segment(a,c),b))
	{
		_d.push_front(a);
		_d.push_back(c);
	}
	else
	{
		_d.push_front(c);
		_d.push_back(a);
	}
	_edges = 3;
	_perimeter = distanceBetweenPoints(a,b) + distanceBetweenPoints(a,c)+ distanceBetweenPoints(b,c);
	_area = abs(areaOfOrientedTriangle(a,b,c));

};
Polygon::~Polygon()
{
	return;
};


// Обробити нову точку
void Polygon::process(const Point& p)
{
	//пропускаємо усі неосвітлені
	for (unsigned int i = 0; i < _edges &&
		!illuminated(Segment(_d.back(), _d.front()), p); ++i) 
	{
		Point temp(_d.front());
		_d.pop_front();
		_d.push_back(temp);
	}
	if(illuminated(Segment(_d.back(),_d.front()),p))
	{
		delEdge(Segment(_d.back(),_d.front()),p);
		//видалимо освітлене ребро
		Point tempFront(_d.front());
		_d.pop_front();

		while(illuminated(Segment(tempFront,_d.front()),p))
		{
			delEdge(Segment(tempFront, _d.front()), p);
			tempFront = _d.front();
			_d.pop_front();
		}//while loop
		_d.push_front(tempFront);

		Point tempBack(_d.back());
		_d.pop_back();
		while (illuminated(Segment(_d.back(), tempBack), p)) {
			delEdge(Segment(_d.back(), tempBack), p);
			tempBack = _d.back();
			_d.pop_back();
		}
		_d.push_back(tempBack);
		addNewEdges(p);
	}
	
	return;
}

void Polygon::addNewEdges(const Point& p)
{
	_edges+=2;
	_perimeter+=distanceBetweenPoints(_d.back(), p) 
		+ distanceBetweenPoints(p, _d.front());
	_d.push_front(p);
}
// Обчислити і запам’ятати периметр
double Polygon::perimeter() const
{
	return _perimeter;
};
// Обчислити і запам’ятати площу
double Polygon::area() const
{
	return _area;
};

bool Polygon::illuminated(const Segment& s, const Point& a) const
{
	if(isPointsOnTheSameLine(s.start(),s.end(),a))
		return !isPointsOnTheSameLine(s.start(),s.end(),a);

	double area(areaOfOrientedTriangle(s.start(),s.end(),a));
	return (area<0);
};
// Замінити сторону sдвома новими сторонами,
// кінцями сторони sі точкою a
void Polygon::delEdge(const Segment& s, const Point& a)
{
	--_edges;
	_perimeter -= s.length();
	_area += abs(areaOfOrientedTriangle(s.start(),a,s.end()));
	return;
};


void Polygon:: showPolygon()
{
	for(size_t i = 0;i<_edges;++i)
	{
		cout<<i<<")"<<_d.front()<<endl;;
		Point p(_d.front());
		_d.pop_front();
		_d.push_back(p);
	}
	cout<<"Perimetr: "<<perimeter()<<endl;
	cout<<"Area: "<<area()<<endl;
	return;
}