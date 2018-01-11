//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Bullet.h"

Bullet::Bullet(const string &filePath, Point coordinates, int _damage) : MoveableObject(filePath, coordinates,BULLET_SPEED),
                                                                        _damage(_damage) {
    type = BULLET;
	speed = BULLET_SPEED;
}


void Bullet::Update(float time) {
    double correctedAngle = this->GetAngle() + 270;

    if (this->GetAngle() > 90)
        correctedAngle = this->GetAngle() - 90;

    double correctedAngleRadians = correctedAngle / 180 * M_PI;

    destination = Point(sin(correctedAngleRadians), -cos(correctedAngleRadians));

    const auto newPostition = _coordinates + (destination * speed * time);
	PhysicsManager::Instance().CheckWallCollision(this, newPostition);
	PhysicsManager::Instance().CheckNewStaticObjectCollision(this, newPostition);
    MoveableObject::Update(time);
}


const int Bullet::GetDamage() const {
    return _damage;
}

void Bullet::SetDamage(int _damage)  {
	this->_damage = _damage;
}

void Bullet::OnBaseCollision(MoveableObject *object) {
}

void Bullet::OnBaseCollision(bool isCollidedOnWall) {
    this->_damage = 0;
    MoveableObject::StopMove();
    MoveableObject::Hide();
}


