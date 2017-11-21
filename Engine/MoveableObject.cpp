//
// Created by Mevl�t �zdemir on 09-11-17.
//


#include "headers/MoveableObject.h"

MoveableObject::MoveableObject(const std::string &filePath, float xPos, float yPos) : xPos{xPos}, yPos{yPos},
                                                                                      distance{0.3f} {
    this->_sprite = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(),
                                                 RenderManager::Instance().LoadImage(filePath));

    if (this->_sprite == NULL) {
        printf(SDL_GetError());
    }

    destinationYPos = 0.0f;
    destinationXPos = 0.0f;


}

void MoveableObject::draw() {
    int w, h;
    SDL_QueryTexture(this->_sprite, nullptr, nullptr, &w, &h);

    SDL_Rect destinationRectangle = {static_cast<int>(xPos), static_cast<int>(yPos), w, h};
    RenderManager::Instance().BlitSurface(this->_sprite, nullptr, &destinationRectangle,
                                          MoveableObject::angle);
}


void MoveableObject::move(Direction direction) {

    if (direction == Direction::Top) {
        moveTop();
        return;
    }

    if (direction == Direction::TopRight) {
        moveTop();
        moveRight();
        return;
    }

    if (direction == Direction::TopLeft) {
        moveTop();
        moveLeft();
        return;
    }

    if (direction == Direction::Right) {
        moveRight();
        return;
    }

    if (direction == Direction::Bottom) {
        moveBottom();
        return;
    }

    if (direction == Direction::BottomRight) {
        moveBottom();
        moveRight();
        return;
    }

    if (direction == Direction::BottomLeft) {
        moveBottom();
        moveLeft();
        return;
    }

    if (direction == Direction::Left) {
        moveLeft();
        return;
    }
}

void MoveableObject::setAngle(int angle) {
    cout << angle << endl;
    MoveableObject::angle = angle;
}

void MoveableObject::moveTop() {
    if (MoveableObject::yPos > 0) {
        setDestinationYPos(-MoveableObject::distance);
    }
}

void MoveableObject::moveRight() {
    int maxWidth = 1500; // todo get max width
    if (MoveableObject::xPos < maxWidth) {
        setDestinationXPos(MoveableObject::distance);
    }
}

void MoveableObject::moveBottom() {
    int maxHeight = 960; // todo get max height
    if (MoveableObject::yPos < maxHeight) {
        setDestinationYPos(MoveableObject::distance);
    }
}

void MoveableObject::moveLeft() {
    if (MoveableObject::xPos > 0) {
        setDestinationXPos(-MoveableObject::distance);
    }
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

    if (xPos < 0) xPos = 0;
    if (xPos > 1500) xPos = 1500;
    if (yPos < 0) yPos = 0;
    if (yPos > 960) yPos = 960;
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
    MoveableObject::destinationXPos = destinationXPos;
}

void MoveableObject::setDestinationYPos(float destinationYPos) {
    MoveableObject::destinationYPos = destinationYPos;
}

float MoveableObject::getDestinationXPos() const {
    return destinationXPos;
}

float MoveableObject::getDestinationYPos() const {
    return destinationYPos;
}

MoveableObject::~MoveableObject() {
  
}


