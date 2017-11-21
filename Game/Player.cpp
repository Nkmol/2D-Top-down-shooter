//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <Weapon.h>
#include "Player.h"

Player::Player(const std::string &filePath, int xPos, int yPos) : MoveableObject(filePath, xPos, yPos, 0.3f) {

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
    if (yPos > 0) {
        setDestinationYPos(-speed);
    }
}

void Player::moveRight() {
    int maxWidth = 1500; // todo get max width
    if (xPos < maxWidth) {
        setDestinationXPos(speed);
    }
}

void Player::moveBottom() {
    int maxHeight = 960; // todo get max height
    if (yPos < maxHeight) {
        setDestinationYPos(speed);
    }
}

void Player::moveLeft() {
    if (xPos > 0) {
        setDestinationXPos(-speed);
    }
}