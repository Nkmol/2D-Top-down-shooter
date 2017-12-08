#include "GameObject.h"

int GameObject::counter = 0;
GameObject::GameObject(const Point coordinates, const int width, const int height) :
	_coordinates(coordinates), width(width), height(height)
{
	visible = true;
	midX = _coordinates.x + width / 2;
	midY = _coordinates.y + height / 2;
	radius = (width + height) / 4;
	this->id = ++counter;

}

GameObject::GameObject(const std::string &spriteToken, const Point coordinates, int spritecount) : _coordinates(coordinates), spritecount(spritecount) {

	for (int i = 0; i < spritecount; i++)
	{
		stringstream ss;
		ss << i;

		_sprite[i] = AssetManager::Instance().LoadTexture(spriteToken + ss.str());
		SDL_QueryTexture(this->_sprite[i], nullptr, nullptr, &this->width, &this->height);

		//SDL_FreeSurface(surface);

		if (this->_sprite == NULL) {
			printf(SDL_GetError());
		}

		visible = true;
		midX = _coordinates.x + width / 2;
		midY = _coordinates.y + height / 2;
		radius = (width + height) / 4;
		this->id = ++counter;
	}
	spritenumber = 0;
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

void GameObject::draw() {
	if (!visible) return;
	

	SDL_Rect destinationRectangle = { static_cast<int>(_coordinates.x), static_cast<int>(_coordinates.y), width, height };
	RenderManager::Instance().DrawTexture(this->_sprite[spritenumber], nullptr, &destinationRectangle, angle);
	if (spritenumber < spritecount - 1) {
		spritenumber = spritenumber + 1;
	}
	else {
		spritenumber = 0;
	}
}

int GameObject::GetId() const {
	return id;
}

void GameObject::SetTeamId(int teamId) {
	GameObject::teamId = teamId;
}

int GameObject::GetTeamId() const {
	return teamId;
}

int GameObject::getAngle() const {
	return angle;
}

void GameObject::SetAngle(const int angle) {
	this->angle = angle;
}

void GameObject::hide() {
	visible = false;
}

bool GameObject::isVisible() const {
	return visible;
}