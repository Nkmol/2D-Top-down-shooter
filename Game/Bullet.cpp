//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Bullet.h"

Bullet::Bullet(const string &filePath, float xPos, float yPos) : MoveableObject(filePath, xPos, yPos, BULLET_SPEED) {}

void Bullet::makeVisible() {
    this->visible = true;
}

void Bullet::makeInvisible() {
    this->visible = false;
}

void Bullet::update(float time) {
    double correctedAngle = this->getAngle() + 270;

    if (this->getAngle() > 90)
        correctedAngle = this->getAngle() - 90;

    double correctedAngleRadians = correctedAngle / 180 * M_PI;
    double destinationXPos = sin(correctedAngleRadians) * BULLET_SPEED;
    double destinationYPos = -cos(correctedAngleRadians) * BULLET_SPEED;

    setDestinationXPos(destinationXPos);
    setDestinationYPos(destinationYPos);

    MoveableObject::update(time);
}
