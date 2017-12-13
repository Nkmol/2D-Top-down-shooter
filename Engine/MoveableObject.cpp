//
// Created by Mevl�t �zdemir on 09-11-17.
//
#include "MoveableObject.h"

MoveableObject::~MoveableObject() {
}

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed) :
        speed{speed}, _destination(Point::Empty()), GameObject::GameObject(filePath, coordinates) {
}

void MoveableObject::draw() {
    if (!visible) return;
    SDL_Rect destinationRectangle = {static_cast<int>(_coordinates.x), static_cast<int>(_coordinates.y),
                                     GameObject::width, GameObject::height};
    RenderManager::Instance().DrawTexture(GameObject::_sprite, nullptr, &destinationRectangle, GameObject::angle);
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

void MoveableObject::SetAnimationTimer(float animationTimer) {
    MoveableObject::animationTimer = animationTimer;
}

void MoveableObject::DecreaseAnimationTimer(float by) {
    MoveableObject::animationTimer -= by;
}

bool MoveableObject::IsReadyForAnimation() const {
    return getAnimationTimer() <= 0;
}

void MoveableObject::ChangeSprite(const std::string &spriteToken) {
    _sprite = AssetManager::Instance().LoadTexture(spriteToken);

    SDL_QueryTexture(this->_sprite, nullptr, nullptr, &this->width, &this->height);
    this->spriteToken = spriteToken;

}

void MoveableObject::setCurrentSpriteIndex(int index) {
    MoveableObject::currentSprite = index;
}


int MoveableObject::GetNextSprite() {
    return ++currentSprite;
}

string MoveableObject::getAnimationToken() {
    return this->spriteToken;
}

bool MoveableObject::AnimationFinished() {
    return currentSprite >= _frames;
}
