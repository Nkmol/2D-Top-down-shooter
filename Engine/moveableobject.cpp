//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include "headers/MoveableObject.h"

MoveableObject::MoveableObject(const std::string &filePath, float xPos, float yPos) : xPos{xPos}, yPos{yPos},
                                                                                      distance{0.2f} {
    this->_sprite = SDL_CreateTextureFromSurface(RenderManager::GetRenderManager()->GetRenderer(),
                                                 RenderManager::GetRenderManager()->LoadImage(filePath));

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
    RenderManager::GetRenderManager()->BlitSurface(this->_sprite, nullptr, &destinationRectangle,
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
    MoveableObject::angle = angle;
}


void MoveableObject::moveTop() {
    if (MoveableObject::yPos > 0) {
        destinationYPos = -MoveableObject::distance;
    }
}

void MoveableObject::moveRight() {
    int maxWidth = 1500; // todo get max width
    if (MoveableObject::xPos < maxWidth) {
        destinationXPos = MoveableObject::distance;
    }
}

void MoveableObject::moveBottom() {
    int maxHeight = 960; // todo get max height
    if (MoveableObject::yPos < maxHeight) {
        destinationYPos = MoveableObject::distance;
    }
}

void MoveableObject::moveLeft() {
    if (MoveableObject::xPos > 0) {
        destinationXPos = -MoveableObject::distance;
    }
}

int MoveableObject::getXPos() const {
    return xPos;
}

int MoveableObject::getYPos() const {
    return yPos;
}

void MoveableObject::update(float time, Direction direction) {
    this->xPos += this->destinationXPos * time;
    this->yPos += this->destinationYPos * time;
}


void MoveableObject::stopMove() {
    this->destinationXPos = 0.0f;
    this->destinationYPos = 0.0f;
}

