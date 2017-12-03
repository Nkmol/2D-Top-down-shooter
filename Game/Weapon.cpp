//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Weapon.h"

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

//// ReSharper disable once CppInconsistentNaming
void to_json(json& j, const Weapon& value)
{
	j = json {
		{ "name", value.getName() },
		{ "maxBullets", value.getMaxBullets() },
		{ "currentBullets", value.getMaxBullets() - value.getShooted()}
	};
}