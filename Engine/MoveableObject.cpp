//
// Created by Mevl�t �zdemir on 09-11-17.
//

#include <AssetManager.h>
#include "MoveableObject.h"

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed) :
        speed{speed}, _destination(Point::Empty()),
        GameObject::GameObject(filePath, coordinates),
        AnimatableObject::AnimatableObject() {
    token = filePath;
}

MoveableObject::~MoveableObject() {
}

void MoveableObject::draw() {
    if (midX < 0) return;

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

void MoveableObject::ChangeSprite(const std::string &spriteToken) {
    _sprite = AssetManager::Instance().loadTexture(spriteToken);

    SDL_QueryTexture(this->_sprite, nullptr, nullptr, &this->width, &this->height);
    this->spriteToken = spriteToken;

}
