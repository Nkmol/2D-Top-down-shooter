//
// Created by Mevlüt Özdemir on 29-11-17.
//

#ifndef SHOOTER_SHOTGUN_H
#define SHOOTER_SHOTGUN_H


#include <Weapon.h>

class Shotgun : public Weapon {

public:
    explicit Shotgun(int damage = 40, float fireRate = 0.5);

};


#endif //SHOOTER_SHOTGUN_H
