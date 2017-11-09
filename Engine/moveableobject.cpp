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

int MoveableObject::getXPos() const {
    return xPos;
}

int MoveableObject::getYPos() const {
    return yPos;
}

void MoveableObject::move(Direction direction) {
    if (direction == Direction::Top) {
        moveTop();
    }

    if (direction == Direction::Right) {
        moveRight();
    }

    if (direction == Direction::Bottom) {
        moveBottom();
    }

    if (direction == Direction::Left) {
        moveLeft();
    }
}

void MoveableObject::moveTop() {
    if (MoveableObject::yPos > 0) {
        MoveableObject::yPos -= 1;
    }
}

void MoveableObject::moveRight() {
    int maxWidth = 10; // todo
    if (MoveableObject::xPos < maxWidth) {
        MoveableObject::xPos += 1;
    }
}

void MoveableObject::moveBottom() {
    int maxHeight = 10;
    if (MoveableObject::yPos < maxHeight) {
        MoveableObject::yPos += 1;
    }
}

void MoveableObject::moveLeft() {
    if (MoveableObject::xPos > 0) {
        MoveableObject::xPos -= 1;
    }
}

void MoveableObject::draw(float x, float y, double angle) {
//    try {
    int w, h;
    SDL_QueryTexture(this->_sprite, NULL, NULL, &w, &h);
    SDL_Rect destinationRectangle = {int(x), int(y), w, h};
    RenderManager::GetRenderManager()->BlitSurface(this->_sprite, NULL, &destinationRectangle, angle);
//    }catch (int e){
//        std::cout << "An exception occurred. Exception Nr. " << e << '\n';
//    }
}



