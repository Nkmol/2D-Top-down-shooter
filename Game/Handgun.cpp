//
// Created by Mevlüt Özdemir on 29-11-17.
//

#include "Handgun.h"

Handgun::Handgun(int damage) : Weapon(damage, "Handgun") {
    Bullet bullet("bullet", 0, 0, damage);
    bullet.makeInvisible();
    this->addBullets(bullet, 10);
}
