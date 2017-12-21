//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_UZI_H
#define SHOOTER_UZI_H


#include "Weapon.h"

class Rifle : public Weapon {

public:
    explicit Rifle(int damage = 15, float fireRate = 0.15);
};


#endif //SHOOTER_UZI_H
