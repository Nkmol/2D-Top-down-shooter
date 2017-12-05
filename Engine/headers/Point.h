//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_POINT_H
#define SHOOTER_POINT_H


class Point {
public:
	Point();
    Point(float x,float y);
	float x,y;

	static Point Left();
	static Point Up();
	static Point Right();
	static Point Down();
	static Point Empty();
	Point operator+(const Point& p) const;
	Point operator*(const float p) const;
	void operator+=(const Point& p);
	Point operator/(const float v) const;
	friend bool operator<(const Point& p1, const Point& p2);
};


#endif //SHOOTER_POINT_H
