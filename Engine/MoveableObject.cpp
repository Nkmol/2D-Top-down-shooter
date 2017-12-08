//
// Created by Mevl�t �zdemir on 09-11-17.
//

#include <AssetManager.h>
#include "MoveableObject.h"
#include "Point.h"

MoveableObject::~MoveableObject()
{
}

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const int spritecount, const float speed) :
        speed{speed}, spritecount{ spritecount }, _destination(Point::Empty()), GameObject::GameObject(filePath, coordinates, spritecount) {
	token = filePath;
	spritenumber = 0;
}

void MoveableObject::draw() {
	if (midX<0);

    if (!visible) return;
    SDL_Rect destinationRectangle = {static_cast<int>(_coordinates.x), static_cast<int>(_coordinates.y), GameObject::width, GameObject::height};
    RenderManager::Instance().DrawTexture(GameObject::_sprite[spritenumber], nullptr, &destinationRectangle, GameObject::angle);
}

int MoveableObject::getAngle() const {
	return angle;
}

void MoveableObject::SetAngle(const int angle) {
	MoveableObject::angle = angle;
}

void MoveableObject::SetCoordinates(const Point& value)
{
	_coordinates = value;
}

const Point &MoveableObject::GetCoordinates() const {
	return _coordinates;
}

void MoveableObject::update(float time) {
    _coordinates += _destination * speed * time;
	if (spritenumber < spritecount - 1) {
		spritenumber = spritenumber + 1;
	}
	else {
		spritenumber = 0;
	}
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