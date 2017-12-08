//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Bullet.h"

Bullet::Bullet(const string &filePath, Point coordinates, int damage) : MoveableObject(filePath, coordinates, 300.0f),
                                                                        damage(damage) {
	_type = BULLET;
}


void Bullet::update(float time) {
    double correctedAngle = this->getAngle() + 270;

    if (this->getAngle() > 90)
        correctedAngle = this->getAngle() - 90;

    double correctedAngleRadians = correctedAngle / 180 * M_PI;

    _destination = Point(sin(correctedAngleRadians), -cos(correctedAngleRadians));

    const auto newPostition = _coordinates + (_destination * speed * time);
	PhysicsManager::Instance().checkWallCollision(this, newPostition);
	MoveableObject::update(time);
}


const int Bullet::getDamage() const {
    return damage;
}

void Bullet::onBaseCollision(MoveableObject* object)
{
	onCollision(object);

}
void Bullet::onBaseCollision(bool isCollidedOnWall)
{
	MoveableObject::stopMove();
	MoveableObject::hide();
}


