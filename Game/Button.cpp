#include "Button.h"

Button::Button(int x1, int y1, int width, int height)
{
	x1Pos = x1;
	y1Pos = y1;
	setX2andY2(x1, y1, width, height);
}

Button::Button() {}
Button::~Button() {}
void Button::setX2andY2(int x1, int y1, int width, int height)
{
	x2Pos = x1 + width;
	y2Pos = y1 + height;
}
int Button::getX1() { return this->x1Pos; }
int Button::getY1() { return this->y1Pos; }
int Button::getY2() { return this->y2Pos; }
int Button::getX2() { return this->x2Pos; }