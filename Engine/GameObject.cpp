#include "GameObject.h"
#include "AssetManager.h"

int GameObject::counter = 0;

GameObject::GameObject(const Point coordinates, const int width, const int height) :
	angle(0),
	_coordinates(coordinates), width(width), height(height)
{
	visible = true;
	midX = _coordinates.x + width / 2;
	midY = _coordinates.y + height / 2;
	radius = (width + height) / 4;
	this->id = ++counter;
}

GameObject::GameObject(const std::string &spriteToken, const Point coordinates) : _coordinates(coordinates) {
    _sprite = AssetManager::Instance().LoadTexture(spriteToken);
	// TODO Move to RenderManager
    SDL_QueryTexture(_sprite->GetTexture(), nullptr, nullptr, &this->width, &this->height);
    visible = true;
    midX = _coordinates.x + width / 2;
    midY = _coordinates.y + height / 2;
    radius = (width + height) / 4;
    this->id = ++counter;
    this->spriteToken = spriteToken;
}

GameObject::GameObject(const GameObject& other) : width(other.width), height(other.height), angle(other.angle),
                                                  radius(other.radius),
                                                  midX(other.midX),
                                                  midY(other.midY),
                                                  _coordinates(other._coordinates), visible(other.visible),
												  // TODO Would be cool to copy this directly
                                                  _sprite(AssetManager::Instance().LoadTexture(other.spriteToken)),
                                                  spriteToken{other.spriteToken}

{
}

GameObject& GameObject::operator=(GameObject that)
{
	Swap(*this, that);
	return *this;
}

GameObject::GameObject() {

}

const int GameObject::getMidX() const {
    return midX;
}

const int GameObject::getMidY() const {
    return midY;
}

const int GameObject::getRadius() const {
    return radius;
}

int GameObject::getWidth() const {
    return width;
}

int GameObject::getHeight() const {
    return height;
}

void GameObject::SetCoordinates(const Point &value) {
    _coordinates = value;
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

    SDL_Rect destinationRectangle = {static_cast<int>(_coordinates.x), static_cast<int>(_coordinates.y), width, height};
    RenderManager::Instance().DrawTexture(_sprite->GetTexture(), nullptr, &destinationRectangle, angle);
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

string GameObject::GetSpriteToken() const {
    return this->spriteToken;
}

