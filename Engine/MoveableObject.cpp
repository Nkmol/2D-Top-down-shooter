//
// Created by Mevl�t �zdemir on 09-11-17.
//

#include <AssetManager.h>
#include "MoveableObject.h"
#include "Point.h"

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed) :
        MoveableObject(filePath, coordinates, speed, 0) {}

MoveableObject::MoveableObject(const std::string &filePath, const Point coordinates, const float speed, int damage) :
        MoveableObject("noname", filePath, coordinates, speed, damage) {}

MoveableObject::MoveableObject(const std::string &name, const std::string &filePath, const Point coordinates,
                               const float speed, int damage) :
        speed{speed},
        _destination(Point::Empty()),
        visible{true},
        GameObject(name, coordinates, 0, 0, damage) {

    SetSprite(filePath);
}

void MoveableObject::SetSprite(const std::string &filePath) {
    SDL_Surface *surface = AssetManager::Instance().loadSurface(filePath);
    if (!surface)
        cout << SDL_GetError() << endl;
    _sprite = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);

    //SDL_FreeSurface(surface);

    if (this->_sprite == nullptr) {
        cout << SDL_GetError() << endl;
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


