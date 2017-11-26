//
// Created by Mevl�t �zdemir on 09-11-17.
//


#include <AssetManager.h>
#include "headers/MoveableObject.h"

MoveableObject::MoveableObject(const std::string &filePath, float xPos, float yPos, float speed)
        : xPos{xPos},
          yPos{yPos},
          speed{speed} {

    SDL_Surface *surface = AssetManager::Instance().loadSurface(filePath);
    if (!surface)
        cout << SDL_GetError() << endl;
    _sprite = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);

    SDL_FreeSurface(surface);

    if (this->_sprite == NULL) {
        printf(SDL_GetError());
    }

    destinationYPos = 0.0f;
    destinationXPos = 0.0f;


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
    this->xPos += this->destinationXPos * time;
    this->yPos += this->destinationYPos * time;
//
//    if (xPos < 0) xPos = 0;
//    if (xPos > 1500) xPos = 1500;
//    if (yPos < 0) yPos = 0;
//    if (yPos > 960) yPos = 960;
}


void MoveableObject::stopMove() {
    this->destinationXPos = 0.0f;
    this->destinationYPos = 0.0f;
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

void MoveableObject::setDestinationXPos(float destinationXPos) {
	if (PhysicsManager::Instance().checkCollision(this->getMidX(destinationXPos), this->getMidY(yPos), this->getRadius())) {
		MoveableObject::destinationXPos = destinationXPos;
	}
}

void MoveableObject::setDestinationYPos(float destinationYPos) {
	if (PhysicsManager::Instance().checkCollision(this->getMidX(xPos), this->getMidY(destinationYPos), this->getRadius())) {
		MoveableObject::destinationYPos = destinationYPos;
	}

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
