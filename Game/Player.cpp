//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include "Player.h"

Player::Player(const std::string &filePath, const float x, const float y)
        : Player(filePath, Point{x, y}) {
}

Player::Player(const std::string &filePath, const Point coordinates, const int lp)
        : MoveableObject(filePath, coordinates, 140.0f), currentWeapon(0), lifepoints(lp) {
}

void Player::addWeapons(std::vector<Weapon> wp) {
    for (auto &weapon : wp) {
        weapons.push_back(weapon);
    }
}

void Player::SetWeapons(const std::vector<Weapon> wp) {
    weapons = wp;
}

int Player::getCurrentWeaponIndex() const {
    return currentWeapon;
}

void Player::changeWeapon(const unsigned index) {
    if (index >= weapons.size() || index < 0) {
        return;
    }

    currentWeapon = index;
}

Bullet Player::shoot() {
    return getWeapon()->getBullet(getAngle(), _coordinates);
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

Weapon *Player::getWeapon() {
    return &weapons[currentWeapon];
}

const vector<Weapon> &Player::getWeapons() const {
    return weapons;
}

void to_json(json &j, const Player &value) {
    j = json{
            {"lifepoints",    value.getLifepoints()},
            {"weapons",       value.getWeapons()},
            {"currentWeapon", value.getCurrentWeaponIndex()}
    };
}

void from_json(const json &j, Player &value) {
    value.changeLifepoints(j.at("lifepoints").get<int>());
    value.changeWeapon(j.at("currentWeapon").get<int>());

    // TODO resolve with wep id -> refactored when weapons are saved in JSON
    auto weps = value.getWeapons();
    auto jsonWeapons = j.at("weapons");
    for (auto i = 0; i < jsonWeapons.size(); i++) {
        from_json(jsonWeapons[i], weps[i]);
    }

    value.SetWeapons(weps);
}

void Player::onCollision(GameObject object) {
    if (object.GetName() == "enemy") {
        this->lifepoints -= object.getDamage();

        if (this->getLifepoints()) {
            this->hide(); // todo: hide or something else
        }
    }
}

