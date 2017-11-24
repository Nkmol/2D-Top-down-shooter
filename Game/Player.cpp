//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <Weapon.h>
#include "Player.h"
#include "Point.h"

Player::Player(const std::string &filePath, int xPos, int yPos) : MoveableObject(filePath, xPos, yPos, 30.0f) {

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

	std::cerr << "Time: " << time << endl;
	std::cerr << "Player speed: " << 7.0 * time << endl;
    MoveableObject::update(time);
}

