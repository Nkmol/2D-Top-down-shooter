//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <Weapon.h>
#include "Player.h"
#include "Point.h"

Player::Player(const std::string &filePath, const float x, const float y)
        : Player(filePath, Point{x, y}) {}

Player::Player(const std::string &filePath, const Point coordinates, const int lp)
        : MoveableObject(filePath, coordinates, 140.0f), lifepoints(lp) {

}

void Player::addWeapons(std::vector<Weapon> wp) {
    for (auto &weapon : wp) {
        weapons.push_back(weapon);
    }
}


void Player::changeWeapon(int index) {
    if (index > 0 && --index < weapons.size()) {
        this->weapon = &weapons[index]; // it returns the weapon on index - 1
    }
}

Bullet Player::shoot() {
    return weapon->getBullet(getAngle(), _coordinates);
}

void Player::Move(const Point direction) {
    _destination = direction;
}

void Player::update(float time) {

    const auto newPostition = _coordinates + (_destination * speed * time);
    if (!PhysicsManager::Instance().checkCollision(getMidX(newPostition.x), getMidY(newPostition.y), getRadius())) {
        MoveableObject::update(time);
    } else {
        MoveableObject::stopMove();
    }

}

const int Player::getLifepoints() const {
    return lifepoints;
}

const int Player::changeLifepoints(const int lp) {
    lifepoints += lp;
    return lifepoints;
}

Weapon *Player::getWeapon() const {
    return weapon;
}

const vector<Weapon>& Player::getWeapons() const
{
	return weapons;
}

// ReSharper disable once CppInconsistentNaming
void to_json(json& j, const Player& value)
{
	j = json{
		{ "lifepoints", value.getLifepoints() },
		{ "weapons", value.getWeapons() },
		{ "currentWeapon", *value.getWeapon() }
	};
}
