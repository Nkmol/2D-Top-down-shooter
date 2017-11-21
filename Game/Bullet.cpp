//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Bullet.h"

Bullet::Bullet(const string &filePath, float xPos, float yPos) : MoveableObject(filePath, xPos, yPos) {}

void Bullet::makeVisible() {
    this->visible = true;
}

void Bullet::makeInvisible() {
    this->visible = false;
}

void Bullet::update(float time) {
    float speed = 1.2;

    double correctedAngle = this->getAngle() + 270;

    if (this->getAngle() > 90)
        correctedAngle = this->getAngle() - 90;

    double correctedAngleRadians = correctedAngle / 180 * M_PI;
    double destinationXPos = sin(correctedAngleRadians) * speed;
    double destinationYPos = -cos(correctedAngleRadians) * speed;

    setDestinationXPos(destinationXPos);
    setDestinationYPos(destinationYPos);

    MoveableObject::update(time);
}
