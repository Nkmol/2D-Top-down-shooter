//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include "headers/MoveableObject.h"

MoveableObject::MoveableObject(const std::string &filePath, int xPos, int yPos) : xPos{xPos}, yPos{yPos} {
    this->_sprite = SDL_CreateTextureFromSurface(RenderManager::GetRenderManager()->GetRenderer(),
                                                 RenderManager::GetRenderManager()->LoadImage(filePath));

    if (this->_sprite == NULL) {
        printf(SDL_GetError());
    }
}

void MoveableObject::draw() {
    int w, h;
    SDL_QueryTexture(this->_sprite, NULL, NULL, &w, &h);
    SDL_Rect destinationRectangle = {int(xPos), int(yPos), w, h};
    RenderManager::GetRenderManager()->BlitSurface(this->_sprite, NULL, &destinationRectangle, angle);
}


void MoveableObject::move(Direction direction) {
    if (direction == Direction::Top) {
        moveTop();
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

    if (direction == Direction::Left) {
        moveLeft();
        return;
    }
}

void MoveableObject::moveTop() {
    if (MoveableObject::yPos > 0) {
        MoveableObject::yPos -= 10;
        MoveableObject::angle = 90;
    }
}

void MoveableObject::moveRight() {
    int maxWidth = 1500; // todo get max width
    if (MoveableObject::xPos < maxWidth) {
        MoveableObject::xPos += 10;
        MoveableObject::angle = 180;
    }
}

void MoveableObject::moveBottom() {
    int maxHeight = 960; // todo get max height
    if (MoveableObject::yPos < maxHeight) {
        MoveableObject::yPos += 10;
        MoveableObject::angle = 270;
    }
}

void MoveableObject::moveLeft() {
    if (MoveableObject::xPos > 0) {
        MoveableObject::xPos -= 10;
        MoveableObject::angle = 360;
    }
}

int MoveableObject::getXPos() const {
    return xPos;
}

int MoveableObject::getYPos() const {
    return yPos;
}



