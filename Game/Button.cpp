#include "Button.h"

Button::Button(int x1, int y1, int width, int height)
{
	setX2andY2(x1, y1, width, height);
}

void Button::setX2andY2(int x1, int y1, int width, int height)
{
	x2 = x1 + width;
	y2 = y1 + height;
}
int Button::getX1() { return this->x1; }
int Button::getY1() { return this->y1; }
int Button::getY2() { return this->y2; }
int Button::getX2() { return this->x2; }