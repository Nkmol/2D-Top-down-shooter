#include "GameObject.h"
int GameObject::counter = 0;
GameObject::GameObject(const Point coordinates, const int width, const int height) :
	_coordinates(coordinates), width(width), height(height)
{
	midX = _coordinates.x + width / 2;
	midY = _coordinates.y + height / 2;
	radius = (width + height) / 4;
	this->id = ++counter;
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

int GameObject::getWidth() const {
    return width;
}

int GameObject::getHeight() const {
    return height;
}

const Point &GameObject::GetCoordinates() const {
	return _coordinates;
}

const SDL_Rect GameObject::GetRect() const {
	SDL_Rect rect = SDL_Rect();
	rect.x = this->_coordinates.x;
	rect.y = this->_coordinates.y;
	rect.w = this->width;
	rect.h = this->height;
	return rect;
}

void GameObject::update(float time) {

}

void GameObject::draw() {

}

int GameObject::GetId() const {
	return id;
}
