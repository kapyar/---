#pragma once
#ifndef _GEOMETRY_H_
#define _GEOMETRY_H_
#include "Point.h"
#include "Segment.h"


inline const double distanceBetweenPoints(const Point & a, const Point & b)
{
	return utDistance(a,b);
}

inline const double areaOfOrientedTriangle(const Point& a,const Point & b, const Point& c)
{
	return ((a.x() - c.x()) * (b.y() - c.y()) - (a.y() - c.y()) * (b.x() - c.x())) * 0.5;
}

inline const bool isPointsOnTheSameLine(const Point& a,const Point & b, const Point& c)
{
	return areaOfOrientedTriangle(a,b,c) == 0;
}



#endif