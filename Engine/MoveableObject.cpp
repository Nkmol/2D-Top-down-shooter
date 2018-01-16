//
// Created by Mevl�t �zdemir on 09-11-17.
//
#include "MoveableObject.h"

MoveableObject::~MoveableObject() {
}

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed) :
        speed{speed}, destination(Point::Empty()), GameObject::GameObject(filePath, coordinates) {
}

void MoveableObject::Update(float time) {
    _coordinates += destination * speed * time;
}

void MoveableObject::StopMove() {
    destination = Point{0, 0};
}

const int MoveableObject::GetPredictionMidX(float destinationPosition) const {
    return destinationPosition + width / 2;;
}

const int MoveableObject::GetMidX() const {
    return _coordinates.x + width / 2;
}

const int MoveableObject::GetMidY() const {
    return _coordinates.y + height / 2;
}

const int MoveableObject::GetPredictionMidY(float destinationPosition) const {
    return destinationPosition + height / 2;
}

classType MoveableObject::GetType() {
    return type;
}

void MoveableObject::OnBaseCollision(MoveableObject *object) {
}

void MoveableObject::OnBaseCollision(bool isWall) {
}

void MoveableObject::OnBaseCollision(GameObject object) {
    //hide();
}


/**************************************************************
 * ALL FOR ANIMATION.. SHOULD ACTUALLY BE IN A ANIMATION OBJECT
 *************************************************************/

const string &MoveableObject::GetState() const {
    return state;
}

void MoveableObject::ChangeState(const string &state) {
    this->state = state;
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

void MoveableObject::ChangeSprite(const std::string &_spriteToken) {
    _sprite = AssetManager::Instance().LoadTexture(_spriteToken);
}

int MoveableObject::NextSpriteIndex() {
    return ++currentSprite;
}

string MoveableObject::GetAnimationToken() {
    return this->_spriteToken;
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
