#include "GameObject.h"
#include "AssetManager.h"

GameObject::GameObject(const Point coordinates, const int width, const int height) :
        angle(0),
        _coordinates(coordinates), width(width), height(height) {
    _visible = true;
    midX = _coordinates.x + width / 2;
    midY = _coordinates.y + height / 2;
    radius = (width + height) / 4;
}

GameObject::GameObject(const std::string &_spriteToken, const Point coordinates) : _coordinates(coordinates) {
    _sprite = AssetManager::Instance().LoadTexture(_spriteToken).release();
    // TODO Move to RenderManager
    SDL_QueryTexture(_sprite->GetTexture(), nullptr, nullptr, &this->width, &this->height);
    _visible = true;
    midX = _coordinates.x + width / 2;
    midY = _coordinates.y + height / 2;
    radius = (width + height) / 4;
    this->_spriteToken = _spriteToken;
}

GameObject::GameObject(const GameObject &other) : width(other.width), height(other.height), angle(other.angle),
                                                  radius(other.radius),
                                                  midX(other.midX),
                                                  midY(other.midY),
                                                  _coordinates(other._coordinates), _visible(other._visible){
    _sprite = other._sprite;
    _spriteToken = other._spriteToken;
}

GameObject &GameObject::operator=(GameObject that) {
    Swap(*this, that);
    return *this;
}

GameObject::GameObject() {

}

void GameObject::SetIsCollidable(bool isCollidable) {
    _isCollidable = isCollidable;
}

const int GameObject::GetMidX() const {
    return midX;
}

const int GameObject::GetMidY() const {
    return midY;
}

const int GameObject::GetRadius() const {
    return radius;
}

int GameObject::GetWidth() const {
    return width;
}

int GameObject::GetHeight() const {
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

void GameObject::Draw() {
    if (!_visible) return;

    SDL_Rect destinationRectangle = {static_cast<int>(_coordinates.x), static_cast<int>(_coordinates.y), width, height};
    RenderManager::Instance().DrawTexture(_sprite->GetTexture(), nullptr, &destinationRectangle, angle);
}

int GameObject::GetAngle() const {
    return angle;
}

void GameObject::SetAngle(const int angle) {
    this->angle = angle;
}

void GameObject::Hide() {
    _visible = false;
}

bool GameObject::IsVisible() const {
    return _visible;
}

string GameObject::GetSpriteToken() const {
    return this->_spriteToken;
}

