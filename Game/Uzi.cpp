//
// Created by Mevlüt Özdemir on 15-11-17.
//

#include "Uzi.h"

Uzi::Uzi(int dmg) {
	damage = dmg;
    Bullet bullet("bullet", 0, 0, damage);
    bullet.makeInvisible();
    Weapon::addBullets(bullet, 100);
}
