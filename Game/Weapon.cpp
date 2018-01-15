//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Weapon.h"
#include "Point.h"
#include "Bullet.h"

Weapon::Weapon(int _damage, std::string name, int maxBullets, float fireRate) :
        name{std::move(name)},
        _damage{_damage},
        maxBullets{maxBullets},
        fireRate{fireRate} {}

Bullet Weapon::GetBullet(int angle, Point coordinates, bool &isCheatActive) {

    double correctedAngle = angle + 270;

    if (angle > 90)
        correctedAngle = angle - 90;

    double correctedAngleRadians = correctedAngle / 180 * M_PI;

    auto radians = static_cast<float>(correctedAngleRadians);

    float gunPosX = coordinates.x + tempX + (tempZ * cos(radians) - (tempY) * sin(radians));
    float gunPosY = coordinates.y + tempX + (tempZ * sin(radians) + (tempY) * cos(radians));

    coordinates.x = gunPosX;
    coordinates.y = gunPosY;

    std::cout << " ***** " << std::endl;
    std::cout << "angle: " << angle << std::endl;
    std::cout << tempX << std::endl;
    std::cout << tempY << std::endl;
    std::cout << tempZ << std::endl;

    Bullet bullet("bullet", coordinates, _damage);
    bullet.SetAngle(angle);

    if (HasBullets()) {
        if (!isCheatActive)
            shooted++;
        else
            bullet.SetDamage(10000000);
    } else {
        bullet.Hide(); // returns a hidden bullet, so it will not be drawn
    }

    return bullet;
}

bool Weapon::HasBullets() {
    return this->shooted < this->maxBullets;
}

int Weapon::TotalBullets() const {
    return maxBullets;
}

std::string Weapon::GetName() const {
    return this->name;
}

const std::string Weapon::GetType() const {
    return type;
}

int Weapon::GetShot() const {
    return this->shooted;
}

int Weapon::GetMaxBullets() const {
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

bool Weapon::CanShoot() const {
    return this->lastShot <= 0;
}

void Weapon::ResetLastShot() {
    this->lastShot = fireRate;
}

void Weapon::UpdateFireRate(float time) {
    this->lastShot -= time;
}

void to_json(nlohmann::json &j, const Weapon &value) {
    j = nlohmann::json {
            {"name",           value.GetName()},
            {"currentBullets", value.GetMaxBullets() - value.GetShot()}
    };
}

void from_json(const nlohmann::json &j, Weapon &value) {
    value.SetName(j.at("name").get<std::string>());
    value.SetCurrentBullets(j.at("currentBullets").get<int>());
}