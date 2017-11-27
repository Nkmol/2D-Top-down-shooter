//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <Weapon.h>
#include "Player.h"
#include "Point.h"

Player::Player(const std::string &filePath, const float x, const float y) : Player(filePath, Point{x, y}) {}

Player::Player(const std::string &filePath, const Point coordinates, const int lp) : MoveableObject(filePath, coordinates, 70.0f), lifepoints(lp) {

}

void Player::addWeapon(Weapon &weapon) {
    Player::weapon = weapon;
}

void Player::shoot() {
    float bulletStartX = _coordinates.x;
    float bulletStartY = _coordinates.y;
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

	const auto newPostition = _coordinates + (_destination * speed * time);
	if (!PhysicsManager::Instance().checkCollision(getMidX(newPostition.x), getMidY(newPostition.y), getRadius())) {
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


