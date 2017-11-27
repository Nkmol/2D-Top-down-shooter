//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <Weapon.h>
#include "Player.h"

Player::Player(const std::string &filePath, int xPos, int yPos, int lp) : MoveableObject(filePath, xPos, yPos, 0.4f), lifepoints(lp) {

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

void Player::move(Direction direction) {

    if (direction == Direction::Top) {
        moveTop();
        return;
    }

    if (direction == Direction::TopRight) {
        moveTop();
        moveRight();
        return;
    }

    if (direction == Direction::TopLeft) {
        moveTop();
        moveLeft();
        return;
    }

    if (direction == Direction::Right) {
        moveRight();
        return;
    }

    if (direction == Direction::Bottom) {
        moveBottom();
        return;
    }

    if (direction == Direction::BottomRight) {
        moveBottom();
        moveRight();
        return;
    }

    if (direction == Direction::BottomLeft) {
        moveBottom();
        moveLeft();
        return;
    }

    if (direction == Direction::Left) {
        moveLeft();
        return;
    }
}


void Player::moveTop() {
    setDestinationYPos(-speed);
}

void Player::moveRight() {
    setDestinationXPos(speed);
}

void Player::moveBottom() {
    setDestinationYPos(speed);
}

void Player::moveLeft() {
    setDestinationXPos(-speed);
}

void Player::draw() {
    weapon.drawBullets();
    MoveableObject::draw();
}

void Player::update(float time) {
    weapon.updateBullets(time);
    MoveableObject::update(time);
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


