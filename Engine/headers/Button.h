#pragma once
#include <string>
#include "GameObject.h"
#include "Event.h"
#include <functional>


class Button : public GameObject {
	typedef function<void()> DelegateFunction;
public:
	// OLD
	Button(const std::string& mediatoken, int x1, int y1, int width, int height);
	// NEW
	Button(const std::string& mediatoken, const Point& startPosition, const Point& size);
	Button(const std::string& mediatoken, const Point& startPosition, const Point& size, const DelegateFunction&& del);
	Button();
	int getX1();
	int getY1();
	int getY2();
	int getX2();
	bool IsClicked(Event ev) const;
	void Click() const;
private:
	DelegateFunction _clickFuncton;

	int x1Pos;
	int x2Pos;
	int y1Pos;
	int y2Pos;
	int width;
	int height;
	void setX2andY2(int, int, int, int);
};
