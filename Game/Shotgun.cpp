//
// Created by Mevlüt Özdemir on 29-11-17.
//

#include "Shotgun.h"

Shotgun::Shotgun(int damage) : Weapon(damage, "Shotgun") {
    Bullet bullet("bullet", 0, 0, damage);
    bullet.makeInvisible();

    this->addBullets(bullet, 5);
}
