//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Bullet.h"

Bullet::Bullet(const string &filePath, Point coordinates, int damage) : MoveableObject(filePath, coordinates, 300.0f),
                                                                        damage(damage) {

}


void Bullet::update(float time) {
    double correctedAngle = this->getAngle() + 270;

    if (this->getAngle() > 90)
        correctedAngle = this->getAngle() - 90;

    double correctedAngleRadians = correctedAngle / 180 * M_PI;

    _destination = Point(sin(correctedAngleRadians), -cos(correctedAngleRadians));

    const auto newPostition = _coordinates + (_destination * speed * time);
    if (!PhysicsManager::Instance().checkOuterWallCollision(getMidX(newPostition.x), getMidY(newPostition.y), getRadius())) {
        MoveableObject::update(time);
    } else {
        // verwerk hier wat er moet gebeuren als er collision is
        MoveableObject::stopMove();
		MoveableObject::hide();
    }
}


const int Bullet::getDamage() const {
    return damage;
}

void Bullet::onCollision(GameObject object)
{
	hide();
}




