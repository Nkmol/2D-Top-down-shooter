//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <Weapon.h>
#include "Player.h"

Player::Player(const std::string &filePath, int xPos, int yPos) : MoveableObject(filePath, xPos, yPos) {

}

void Player::addWeapon(Weapon &weapon) {
    Player::weapon = weapon;
}

void Player::shoot() {
    float bulletStartX = getXPos();
    float bulletStartY = getYPos();
    Player::weapon.shoot(getAngle(), bulletStartX, bulletStartY);
}

Weapon & Player::getWeapon() {
    return weapon;
}
