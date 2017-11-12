//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include "headers/MoveableObject.h"

MoveableObject::MoveableObject(const std::string &filePath, int xPos, int yPos) : xPos{xPos}, yPos{yPos}, speed{10} {
    this->_sprite = SDL_CreateTextureFromSurface(RenderManager::GetRenderManager()->GetRenderer(),
                                                 RenderManager::GetRenderManager()->LoadImage(filePath));

    if (this->_sprite == NULL) {
        printf(SDL_GetError());
    }

    MoveableObject::directionAngles = {
            {Direction::TopLeft,     45},
            {Direction::Top,         90},
            {Direction::TopRight,    135},
            {Direction::Right,       180},
            {Direction::BottomRight, 225},
            {Direction::Bottom,      270},
            {Direction::BottomLeft,  315},
            {Direction::Left,        360}
    };
}

void MoveableObject::draw() {
    int w, h;
    SDL_QueryTexture(this->_sprite, nullptr, nullptr, &w, &h);
    SDL_Rect destinationRectangle = {xPos, yPos, w, h};
    RenderManager::GetRenderManager()->BlitSurface(this->_sprite, nullptr, &destinationRectangle,
                                                   MoveableObject::angle);
}


void MoveableObject::move(Direction direction) {

    // TODO: REFACTOR
//    MoveableObject::setAngle(direction);

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

void MoveableObject::setAngle(Direction direction) {
    auto search = directionAngles.find(direction);

    if (search != directionAngles.end()) {
        MoveableObject::angle = search->second; // search->first is the key.. search->second is the value..
    }
}

void MoveableObject::setAngle(int angle) {
    MoveableObject::angle = angle;
}


void MoveableObject::moveTop() {
    if (MoveableObject::yPos > 0) {
        MoveableObject::yPos -= MoveableObject::speed;
    }
}

void MoveableObject::moveRight() {
    int maxWidth = 1500; // todo get max width
    if (MoveableObject::xPos < maxWidth) {
        MoveableObject::xPos += MoveableObject::speed;
    }
}

void MoveableObject::moveBottom() {
    int maxHeight = 960; // todo get max height
    if (MoveableObject::yPos < maxHeight) {
        MoveableObject::yPos += MoveableObject::speed;
    }
}

void MoveableObject::moveLeft() {
    if (MoveableObject::xPos > 0) {
        MoveableObject::xPos -= MoveableObject::speed;
    }
}

int MoveableObject::getXPos() const {
    return xPos;
}

int MoveableObject::getYPos() const {
    return yPos;
}




