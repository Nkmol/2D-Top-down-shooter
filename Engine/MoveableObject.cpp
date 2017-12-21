//
// Created by Mevl�t �zdemir on 09-11-17.
//
#include "MoveableObject.h"

MoveableObject::~MoveableObject() {
}

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed) :
        speed{speed}, _destination(Point::Empty()), GameObject::GameObject(filePath, coordinates) {
}

void MoveableObject::update(float time) {
    _coordinates += _destination * speed * time;
}

void MoveableObject::stopMove() {
    _destination = Point{0, 0};
}

const int MoveableObject::getPredictionMidX(float destinationPosition) const {
    return destinationPosition + width / 2;;
}

const int MoveableObject::getMidX() const {
    return _coordinates.x + width / 2;
}

const int MoveableObject::getMidY() const {
    return _coordinates.y + height / 2;
}

const int MoveableObject::getPredictionMidY(float destinationPosition) const {
    return destinationPosition + height / 2;
}

classType MoveableObject::getType() {
    return _type;
}

void MoveableObject::onBaseCollision(MoveableObject *object) {
}

void MoveableObject::onBaseCollision(bool isWall) {
}

void MoveableObject::onBaseCollision(GameObject object) {
    //hide();
}


/**************************************************************
 * ALL FOR ANIMATION.. SHOULD ACTUALLY BE IN A ANIMATION OBJECT
 *************************************************************/

const string &MoveableObject::GetState() const {
    return _state;
}

void MoveableObject::ChangeState(const string &_state) {
    this->_state = _state;
    this->currentSprite = -1; // will be 0 on animation
}

void MoveableObject::HandleAnimationFinished() {
    this->currentSprite = -1; // will be 0 on animation
}

void MoveableObject::DecreaseAnimationTimer(double by) {
    MoveableObject::currentAnimationTimer -= by;
}

bool MoveableObject::IsReadyForAnimation() const {
    return currentAnimationTimer <= 0;
}

void MoveableObject::ChangeSprite(const std::string &spriteToken) {
    _sprite = AssetManager::Instance().LoadTexture(spriteToken);
}

int MoveableObject::NextSpriteIndex() {
    return ++currentSprite;
}

string MoveableObject::GetAnimationToken() {
    return this->spriteToken;
}

bool MoveableObject::IsAnimationFinished() {
    return currentSprite >= frames;
}

void MoveableObject::ResetAnimationTimer() {
    currentAnimationTimer = animationTimer;
}

void MoveableObject::SetSpeed(float speed) {
    MoveableObject::speed = speed;
}

float MoveableObject::GetSpeed() const {
    return speed;
}
