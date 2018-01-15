#ifndef SHOOTER_POINT_H
#define SHOOTER_POINT_H
#include <ostream>

class Point {
public:
	float x, y;

	Point() : Point(0, 0)
	{
	}

	Point(const float x, const float y) : x{ x }, y{ y } {

	}

	static Point Left()
	{
		return Point{ -1, 0 };
	}

	static Point Up()
	{
		return Point{ 0, -1 };
	}

	static Point Right()
	{
		return Point{ 1, 0 };
	}

	static Point Down()
	{
		return Point{ 0, 1 };
	}

	static Point Empty()
	{
		return Point();
	}

	Point operator+(const Point& p) const
	{
		return Point{ p.x + x, p.y + y };
	}

	Point operator-(const Point& p) const
	{
		return Point{ x - p.x, y - p.y };
	}

	Point operator-(const float val) const
	{
		return Point{ x - val, y - val };
	}

	Point operator*(const float v) const
	{
		return Point{ x * v, y * v };
	}

	Point operator*(const Point& v) const
	{
		return Point{ x * v.x, y * v.y };
	}

	Point operator/(const Point& v) const
	{
		return Point{ x / v.x, y / v.y };
	}


	void operator+=(const Point& p)
	{
		x += p.x;
		y += p.y;
	}

	void operator-=(const Point& p)
	{
		x -= p.x;
		y -= p.y;
	}

	
	Point& operator-=(const float value)
	{
		x -= value;
		y -= value;

		return *this;
	}

	Point& operator+=(const float& value)
	{
		x += value;
		y += value;

		return *this;
	}


	void operator*=(const float p)
	{
		x *= p;
		y *= p;
	}

	void operator/=(const float p)
	{
		x /= p;
		y /= p;
	}

	void operator/=(const Point& p)
	{
		x /= p.x;
		y /= p.y;
	}

	bool operator>(const float p) const
	{
		return p > x || p > y;
	}

	bool operator>(const Point& p) const
	{
		return x > p.x || y > p.y;
	}

	bool operator>=(const Point& p) const
	{
		return x >= p.x && y >= p.y;
	}

	bool operator==(const Point& p) const
	{
		return x == p.x && y == p.y;
	}

	bool operator!=(const Point& p) const
	{
		return x != p.x && y != p.y;
	}

	bool operator<=(const Point& p) const
	{
		return x <= p.x && y <= p.y;
	}

	bool operator<(const float p) const
	{
		return p < x || p < y;
	}

	Point operator/(const float v) const
	{
		return Point{ x / v, y / v };
	}

	float dist(const Point& v) const {
		Point d{v.x - x, v.y - y};
		return d.length();
	}

	float dist_squared(const Point v) const
	{
		return (x - v.x) * (x - v.x) + (y - v.y) * (y - v.y);
	}

	float length() const {
		return std::sqrt(x * x + y * y);
	}

	float length_squared() const
	{
		return x * x + y * y;
	}

	Point& set_magnitude(const float len)
	{
		normalize();
		*this = *this * len;

		return *this;
	}

	Point& normalize() {
		const auto m = length();
		if(m != 0 && m != 1)
		{
			*this /= m;
		}
		
		return *this;
	}

	// Do not save normalized value to given instance
	static Point normalize(const Point& p) {
		if (p.length() == 0) return p;

		return p / p.length();
	}

	Point& limit(const float limit_value)
	{
		if(length_squared() > limit_value * limit_value)
		{
			normalize();
			*this = *this * limit_value;
		}

		return *this;
	}
};


inline std::ostream& operator<<(std::ostream& os, const Point& obj)
{
	os << "[ " << obj.x << ", " << obj.y << " ]";

	return os;
}

#endif //SHOOTER_POINT_H
