//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_WEAPON_H
#define SHOOTER_WEAPON_H


#include <iostream>
#include "Bullet.h"
#include <vector>
#include <memory>

class Weapon {

protected:
    int damage;
    int maxBullets;
    int shooted = 0;
    std::string name;

public:
    Weapon(int damage, std::string name, int maxBullets);

    bool hasBullets();

    Bullet getBullet(int angle, Point coordinates);

    int totalBullets() const;

    int getShooted() const;

    std::string getName() const;
};


#endif //SHOOTER_WEAPON_H
