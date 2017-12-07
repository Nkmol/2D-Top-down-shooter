//
// Created by Mevl�t �zdemir on 09-11-17.
//


#include "MoveableObject.h"

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed) :

        speed{speed}, _destination(Point::Empty()), GameObject::GameObject(filePath, coordinates) {
	token = filePath;
}

void MoveableObject::draw() {
	if (midX<0);

    if (!visible) return;
    SDL_Rect destinationRectangle = {static_cast<int>(_coordinates.x), static_cast<int>(_coordinates.y), GameObject::width, GameObject::height};
    RenderManager::Instance().DrawTexture(GameObject::_sprite, nullptr, &destinationRectangle, GameObject::angle);
}



void MoveableObject::update(float time) {
    _coordinates += _destination * speed * time;
}


void MoveableObject::stopMove() {
    _destination = Point{0, 0};
}

void MoveableObject::hide() {
    this->visible = false;
}

classType MoveableObject::getType()
{
	return _type;
}

const int MoveableObject::getMidX() const
{
	return _coordinates.x + width / 2;
}

const int MoveableObject::getMidY() const
{
	return _coordinates.y + height / 2;
}

void MoveableObject::onBaseCollision(MoveableObject* object)
{
}

void MoveableObject::onBaseCollision(bool isWall)
{
}

void MoveableObject::onBaseCollision(GameObject object)
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

const int MoveableObject::getPredictionMidX(float destinationPosition) const
{
	return destinationPosition + width / 2;
}

const int MoveableObject::getPredictionMidY(float destinationPosition) const
{
	return destinationPosition + height / 2;
}