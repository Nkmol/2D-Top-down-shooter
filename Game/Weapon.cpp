//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Weapon.h"

Weapon::Weapon(int damage, std::string name, int maxBullets) : name{std::move(name)}, damage{damage},
                                                               maxBullets{maxBullets} {

}

Bullet Weapon::getBullet(int angle, Point coordinates) {
    if (hasBullets()) {
        shooted++;

        Bullet b("bullet", coordinates, damage);
        b.setAngle(angle);

        return b;
    }

    return Bullet("bullet", Point(-20,-20), 0); // todo return NullBulletObject
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


