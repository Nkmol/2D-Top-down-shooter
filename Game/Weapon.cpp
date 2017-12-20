//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Weapon.h"
#include "Point.h"
#include "Bullet.h"

Weapon::Weapon(int damage, std::string name, int maxBullets, float fireRate) :
        name{std::move(name)},
        damage{damage},
        maxBullets{maxBullets},
        fireRate{fireRate} {}

Bullet Weapon::getBullet(int angle, Point coordinates) {
    Bullet bullet("bullet", coordinates, damage);
    bullet.SetAngle(angle);

    if (hasBullets()) {
        shooted++;
    } else {
        bullet.hide(); // returns a hidden bullet, so it will not be drawn
    }

    return bullet;
}

bool Weapon::hasBullets() {
    return this->shooted < this->maxBullets;
}

int Weapon::totalBullets() const {
    return maxBullets;
}

std::string Weapon::getName() const {
    return this->name;
}

int Weapon::getShot() const {
    return this->shooted;
}

int Weapon::getMaxBullets() const {
    return maxBullets;
}

void Weapon::SetName(const std::string &v) {
    name = v;
}

void Weapon::SetCurrentBullets(const int v) {
    shooted = maxBullets - v;
}

void Weapon::Reload() {
    this->shooted = 0;
}

bool Weapon::CanReload() const {
    return shooted > 0;
}

bool Weapon::CanShoot() const{
    return this->lastShot <= 0;
}

void Weapon::ResetLastShot(){
    this->lastShot = fireRate;
}

void Weapon::UpdateFireRate(float time) {
    this->lastShot -= time;
}

void to_json(nlohmann::json &j, const Weapon &value) {
    j = nlohmann::json {
            {"name",           value.getName()},
            {"currentBullets", value.getMaxBullets() - value.getShot()}
    };
}

void from_json(const nlohmann::json &j, Weapon &value) {
    value.SetName(j.at("name").get<std::string>());
    value.SetCurrentBullets(j.at("currentBullets").get<int>());
}