//
// Created by Mevl�t �zdemir on 09-11-17.
//

#include <AssetManager.h>
#include "Point.h"
#include "MoveableObject.h"
#include "PhysicsManager.h"

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed) :
        speed{speed},
        _destination(Point::Empty()),
        _coordinates(coordinates),
        visible{true} {

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
    SDL_QueryTexture(this->_sprite, nullptr, nullptr, &width, &height);

    SDL_Rect destinationRectangle = {static_cast<int>(_coordinates.x), static_cast<int>(_coordinates.y), width, height};
    RenderManager::Instance().DrawTexture(this->_sprite, nullptr, &destinationRectangle, angle);
}

void MoveableObject::SetAngle(const int angle) {
    MoveableObject::angle = angle;
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

int MoveableObject::getAngle() const {
    return angle;
}

void MoveableObject::hide() {
    this->visible = false;
}

void MoveableObject::onCollision(MoveableObject moveableObject)
{
	hide();
}

bool MoveableObject::isVisible() const {
    return visible;
}

MoveableObject::~MoveableObject() {
    // if sdl_destroytexture is called, the bullet's image cannot be found
    //    SDL_DestroyTexture(_sprite);
}

const int MoveableObject::getMidX(float destinationPosition) const {
    return destinationPosition + width / 2;;
}

const int MoveableObject::getMidY(float destinationPosition) const {
    return destinationPosition + height / 2;
}

const int MoveableObject::getRadius() const {
    return (width + height) / 4;
}

int MoveableObject::getWidth() const {
    return width;
}

int MoveableObject::getHeight() const {
    return height;
}