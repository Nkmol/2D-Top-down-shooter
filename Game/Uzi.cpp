//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Uzi.h"

Uzi::Uzi(int damage) : Weapon(damage, "Uzi") {
    Bullet bullet("bullet", 0, 0, damage);
    bullet.makeInvisible();

    this->addBullets(bullet, 100);
}
