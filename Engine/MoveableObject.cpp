//
// Created by Mevl�t �zdemir on 09-11-17.
//


#include "MoveableObject.h"

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed) :
        speed{speed},
        _destination(Point::Empty()),
        GameObject(coordinates, 0, 0) {
	visible = true;
	_type = MOVEABLEOBJECT;
    SDL_Surface *surface = AssetManager::Instance().loadSurface(filePath);
    if (!surface)
        cout << SDL_GetError() << endl;
    _sprite = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);

    //SDL_FreeSurface(surface);

    if (this->_sprite == NULL) {
        printf(SDL_GetError());
    }
}

void MoveableObject::draw() {
    if (!visible) return;
    SDL_QueryTexture(this->_sprite, nullptr, nullptr, &this->width, &this->height);

    SDL_Rect destinationRectangle = {static_cast<int>(_coordinates.x), static_cast<int>(_coordinates.y), width, height};
    RenderManager::Instance().DrawTexture(this->_sprite, nullptr, &destinationRectangle, angle);
    GameObject::draw();
}

void MoveableObject::SetAngle(const int angle) {
    MoveableObject::angle = angle;
}

void MoveableObject::update(float time) {
    _coordinates += _destination * speed * time;
    GameObject::update(time);
}


void MoveableObject::stopMove() {
    _destination = Point{0, 0};
}


int MoveableObject::getAngle() const {
    return angle;
}

void MoveableObject::hide() {
    this->visible = false;
}

classType MoveableObject::getType()
{
	return _type;
}

void MoveableObject::onBaseCollision(shared_ptr<MoveableObject> moveableObject)
{
	//hide();
}

void MoveableObject::onCollision(bool isCollidedOnWall)
{
}



MoveableObject::~MoveableObject() {
    // if sdl_destroytexture is called, the bullet's image cannot be found
    //    SDL_DestroyTexture(_sprite);
}

const int MoveableObject::getMidX() const {
	return _coordinates.x + width / 2;
}

const int MoveableObject::getMidY() const {
    return _coordinates.y + height / 2;
}

const int MoveableObject::getPredictionMidX(float destinationPosition) const
{
	return destinationPosition + width / 2;
}

const int MoveableObject::getPredictionMidY(float destinationPosition) const
{
	return destinationPosition + height / 2;
}