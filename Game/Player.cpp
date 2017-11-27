//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <Weapon.h>
#include "Player.h"
#include "Point.h"

Player::Player(const std::string &filePath, int xPos, int yPos, int lp) : MoveableObject(filePath, xPos, yPos, 140.0f), lifepoints(lp) {

}

void Player::addWeapon(Weapon &weapon) {
    Player::weapon = weapon;
}

void Player::shoot() {
    float bulletStartX = getXPos();
    float bulletStartY = getYPos();
    weapon.shoot(getAngle(), bulletStartX, bulletStartY);
}

Weapon &Player::getWeapon() {
    return weapon;
}

void Player::Move(const Point direction) {
	_destination = direction;
}

void Player::draw() {
    weapon.drawBullets();
    MoveableObject::draw();
}

void Player::update(float time) {
	weapon.updateBullets(time);
	if (!PhysicsManager::Instance().checkCollision(getMidX(xPos + _destination.x * speed * time), getMidY(yPos + _destination.y * speed * time), getRadius())) {
		MoveableObject::update(time);
	}
	else {
		MoveableObject::stopMove();
	}

}

const int Player::getLifepoints() const
{
	return lifepoints;
}

const int Player::changeLifepoints(const int lp)
{
	lifepoints += lp;
	return lifepoints;
}


