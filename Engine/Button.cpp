#include "AssetManager.h"
#include "Button.h"
#include "Event.h"
#include "InputManager.h"


Button::Button(const std::string& mediatoken, int x1, int y1, int width, int height) : GameObject(Point(x1, y1), width, height) {
	x1Pos = x1;
	y1Pos = y1;
	setX2andY2(x1, y1, width, height);
	
	// TODO Let GameObject handle this
	GameObject::_sprite = AssetManager::Instance().LoadTexture(mediatoken);
	GameObject::_spriteToken = mediatoken;
}

Button::Button(const std::string& mediatoken, const Point& startPosition, const Point& size) : Button(mediatoken, startPosition.x, startPosition.y, size.x, size.y)
{
}

Button::Button(const std::string& mediatoken, const Point& startPosition, const Point& size, const DelegateFunction&& delegate) : Button(mediatoken, startPosition, size)
{
	_clickFuncton = move(delegate);
}

Button::Button() {}

void Button::setX2andY2(int x1, int y1, int width, int height)
{
	x2Pos = x1 + width;
	y2Pos = y1 + height;
}

bool Button::IsClicked(Event ev) const
{
	if (!InputManager::Instance().IsMouseClicked(ev)) return false;

	auto& mouse = ev.GetEventValue().button;
	return mouse.x > x1Pos && mouse.x < x2Pos && mouse.y > y1Pos && mouse.y < y2Pos;
}

void Button::Click() const
{
	_clickFuncton();
}

int Button::getX1() { return this->x1Pos; }
int Button::getY1() { return this->y1Pos; }
int Button::getY2() { return this->y2Pos; }
int Button::getX2() { return this->x2Pos; }