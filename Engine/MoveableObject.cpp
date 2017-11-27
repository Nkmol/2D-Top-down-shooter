//
// Created by Mevl�t �zdemir on 09-11-17.
//


#include <AssetManager.h>
#include "headers/MoveableObject.h"
#include "Point.h"

MoveableObject::MoveableObject(const std::string &filePath, float xPos, float yPos, float speed)
	: speed{speed},
	  xPos{xPos}, 
	  yPos{yPos},
	  _destination(Point::Empty())
{
	SDL_Surface* surface = AssetManager::getInstance().loadSurface(filePath);
	if (!surface)
		cout << SDL_GetError() << endl;
	_sprite = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);

	SDL_FreeSurface(surface);

	if (this->_sprite == NULL)
	{
		printf(SDL_GetError());
	}

	//destinationYPos = 0.0f;
	//destinationXPos = 0.0f;
}

void MoveableObject::draw() {
    int w, h;
    SDL_QueryTexture(this->_sprite, nullptr, nullptr, &w, &h);

    SDL_Rect destinationRectangle = {static_cast<int>(xPos), static_cast<int>(yPos), w, h};
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
//
//    if (xPos < 0) xPos = 0;
//    if (xPos > 1500) xPos = 1500;
//    if (yPos < 0) yPos = 0;
//    if (yPos > 960) yPos = 960;
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


