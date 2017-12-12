//
// Created by Mevl�t �zdemir on 09-11-17.
//

#include <AssetManager.h>
#include "MoveableObject.h"
#include "Point.h"

MoveableObject::~MoveableObject() {
}

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed) :
        speed{speed}, _destination(Point::Empty()), GameObject::GameObject(filePath, coordinates) {
    token = filePath;
    this->_state = "idle";
    this->_frames = 0;
    this->animationTimer = 0.1f;

}

void MoveableObject::draw() {
    if (midX < 0);

    if (!visible) return;
    SDL_Rect destinationRectangle = {static_cast<int>(_coordinates.x), static_cast<int>(_coordinates.y),
                                     GameObject::width, GameObject::height};
    RenderManager::Instance().DrawTexture(GameObject::_sprite, nullptr, &destinationRectangle, GameObject::angle);
}

int MoveableObject::getAngle() const {
    return angle;
}

void MoveableObject::SetAngle(const int angle) {
    MoveableObject::angle = angle;
}

void MoveableObject::SetCoordinates(const Point &value) {
    _coordinates = value;
}

const Point &MoveableObject::GetCoordinates() const {
    return _coordinates;
}

void MoveableObject::update(float time) {
    _coordinates += _destination * speed * time;
}


void MoveableObject::stopMove() {
    _destination = Point{0, 0};
}

const int MoveableObject::getMidX(float destinationPosition) const {
    return destinationPosition + width / 2;;
}

const int MoveableObject::getMidY(float destinationPosition) const {
    return destinationPosition + height / 2;
}

const string &MoveableObject::GetState() const {
    return _state;
}

void MoveableObject::SetState(const string &_state) {
    this->_state = _state;
    setCurrentSpriteIndex(-1);
}


void MoveableObject::SetFrames(int _frames) {
    MoveableObject::_frames = _frames;
}

void MoveableObject::HandleAnimationFinished() {
    setCurrentSpriteIndex(-1);
}

float MoveableObject::getAnimationTimer() const {
    return animationTimer;
}

void MoveableObject::setAnimationTimer(float animationTimer) {
    MoveableObject::animationTimer = animationTimer;
}

void MoveableObject::DecreaseAnimationTimer(float by) {
    MoveableObject::animationTimer -= by;
}

bool MoveableObject::readyForAnimation() const {
    return getAnimationTimer() <= 0;
}

void MoveableObject::changeSprite(const std::string &spriteToken) {
    _sprite = AssetManager::Instance().loadTexture(spriteToken);

    SDL_QueryTexture(this->_sprite, nullptr, nullptr, &this->width, &this->height);
    this->spriteToken = spriteToken;

}

void MoveableObject::setCurrentSpriteIndex(int index) {
    MoveableObject::currentSprite = index;
}


int MoveableObject::getNextSpriteIndex() {
    return ++currentSprite;
}

string MoveableObject::getAnimationToken() {
    return this->token;
}

bool MoveableObject::AnimationFinished() {
    return currentSprite >= _frames;
}
