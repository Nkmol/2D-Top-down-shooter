//
// Created by Mevl�t �zdemir on 09-11-17.
//


#include <AssetManager.h>
#include "headers/MoveableObject.h"
#include "Point.h"

MoveableObject::MoveableObject(const std::string &filePath, float xPos, float yPos, float speed)
	: speed{ speed },
	xPos{ xPos },
	yPos{ yPos },
	_destination(Point::Empty())
{

    SDL_Surface *surface = AssetManager::Instance().loadSurface(filePath);
    if (!surface)
        cout << SDL_GetError() << endl;
    _sprite = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);

    SDL_FreeSurface(surface);

    if (this->_sprite == NULL) {
        printf(SDL_GetError());
    }
}

void MoveableObject::draw() {

    SDL_QueryTexture(this->_sprite, nullptr, nullptr, &width, &height);

    SDL_Rect destinationRectangle = {static_cast<int>(xPos), static_cast<int>(yPos), width, height};
    RenderManager::Instance().BlitSurface(this->_sprite, nullptr, &destinationRectangle,
                                          MoveableObject::angle);
}

void MoveableObject::setAngle(int angle) {
    MoveableObject::angle = angle;
}


float MoveableObject::getXPos() const {
    return xPos;
}

float MoveableObject::getYPos() const {
    return yPos;
}


void MoveableObject::update(float time) {
	this->xPos += _destination.x * speed * time;
	this->yPos += _destination.y * speed * time;
}


void MoveableObject::stopMove() {
	_destination = Point{ 0, 0 };
}

int MoveableObject::getAngle() const {
    return angle;
}

void MoveableObject::setXPos(float xPos) {
    MoveableObject::xPos = xPos;
}

void MoveableObject::setYPos(float yPos) {
    MoveableObject::yPos = yPos;
}

bool MoveableObject::isVisible() const {
    return visible;
}

MoveableObject::~MoveableObject() {
    // if sdl_destroytexture is called, the bullet's image cannot be found
    //    SDL_DestroyTexture(_sprite);
}

const int MoveableObject::getMidX(float destinationPosition) const
{
	return  destinationPosition +  width / 2;;
}

const int MoveableObject::getMidY(float destinationPosition) const
{
	return destinationPosition + height / 2;
}

const int MoveableObject::getRadius() const
{
	return (width + height) / 4;
}
