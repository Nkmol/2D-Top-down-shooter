//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Uzi.h"

Uzi::Uzi() {
    Bullet bullet("bullet", 0, 0);
    bullet.makeInvisible();
    Weapon::addBullets(bullet, 100);
}
