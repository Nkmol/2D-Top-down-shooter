#include "GameObject.h"

GameObject::GameObject(const std::string mediatoken, float x, const float y, const int width, const int height) :
	x(x), y(y), width(width), height(height) 
{
	midX = x + width / 2;
	midY = y + height / 2;
	radius = (width + height) / 4;
}

GameObject::GameObject()
{

}

const int GameObject::getMidX() const
{
	return midX;
}

const int GameObject::getMidY() const
{
	return midY;
}

const int GameObject::getRadius() const
{
	return radius;
}
