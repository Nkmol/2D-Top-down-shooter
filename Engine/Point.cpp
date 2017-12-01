//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "Point.h"

Point::Point() : Point(0, 0)
{
}

Point::Point(const float x, const float y) : x{x}, y{y}{

}

Point Point::Left()
{
	return Point{ -1, 0 };
}

Point Point::Up()
{
	return Point{ 0, -1 };
}

Point Point::Right()
{
	return Point{ 1, 0 };
}

Point Point::Down()
{
	return Point{ 0, 1 };
}

Point Point::Empty()
{
	return Point();
}

Point Point::operator+(const Point& p) const
{
	return Point{ p.x + x, p.y + y };
}

Point Point::operator*(const float v) const
{
	return Point{ x * v, y * v };
}

void Point::operator+=(const Point& p)
{
	x += p.x;
	y += p.y;
}

Point Point::operator/(const float v) const
{
	return Point(x / v, y / v);
}


bool operator<(const Point &p1, const Point &p2) {
	return (p1.x == p2.x && p1.y == p2.y);
}
