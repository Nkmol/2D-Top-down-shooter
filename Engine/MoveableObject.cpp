//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include "headers/MoveableObject.h"
#include "headers/Direction.h"


int MoveableObject::getXPos() const {
    return xPos;
}

int MoveableObject::getYPos() const {
    return yPos;
}

void MoveableObject::setXPos(int xPos) {
    MoveableObject::xPos = xPos;
}

void MoveableObject::setYPos(int yPos) {
    MoveableObject::yPos = yPos;
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
