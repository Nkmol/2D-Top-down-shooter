//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Weapon.h"
#include "Point.h"
#include "Bullet.h"

Weapon::Weapon(int damage, std::string name, int maxBullets) :
        name{std::move(name)},
        damage{damage},
        maxBullets{maxBullets} {}

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

void Weapon::Reload(){
    shooted = 0;
}

int Weapon::totalBullets() const {
    return maxBullets;
}

std::string Weapon::getName() const {
    return this->name;
}

int Weapon::getShooted() const {
    return this->shooted;
}

int Weapon::getMaxBullets() const {
	return maxBullets;
}

void Weapon::SetName(const std::string& v)
{
	name = v;
}

void Weapon::SetCurrentBullets(const int v)
{
	shooted = maxBullets - v;
}

void to_json(nlohmann::json& j, const Weapon& value)
{
	j = nlohmann::json {
		{ "name", value.getName() },
		{ "currentBullets", value.getMaxBullets() - value.getShooted()}
	};
}

void from_json(const nlohmann::json& j, Weapon& value)
{
	value.SetName(j.at("name").get<std::string>());
	value.SetCurrentBullets(j.at("currentBullets").get<int>());
}