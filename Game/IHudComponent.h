#pragma once
#include "Point.h"

class IHudComponent
{
protected:
	Point _pos;
	int _w, _h;
	double _angle;
	float _lifetime;
	float _livingtime = 0.0f;
public:
	IHudComponent(Point pos, int w, int h, float time, double angle = 0) : _pos{ pos }, _w(w), _h(h), _angle(angle), _lifetime(time) {};

	virtual void Update(float time) = 0;
	virtual void Draw() = 0;

	Point GetOffSet() const { return _pos; }
	void SetOffset(Point newPos) {
		_pos = newPos;
	}
	const int GetWidth() const { return _w; }
	const int GetHeight() const { return _h; }

	const bool Destroyable() const { return (_livingtime > _lifetime); }
};