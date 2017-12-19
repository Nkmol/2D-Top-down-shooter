//
// Created by Mevlüt Özdemir on 29-11-17.
//

#ifndef SHOOTER_HANDGUN_H
#define SHOOTER_HANDGUN_H


#include <Weapon.h>

class Handgun : public Weapon {

public:
    explicit Handgun(int damage = 20, float fireRate = 0.25);
};


#endif //SHOOTER_HANDGUN_H
