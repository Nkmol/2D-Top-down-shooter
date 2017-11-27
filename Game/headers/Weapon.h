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
    std::vector<Bullet> bullets;

	int damage;
public:
    const vector<Bullet> &getBullets() const;

    void shoot(int angle, float xPos, float yPos);

    void addBullets(Bullet &bullet, int amount);

    void updateBullets(float time);

    void drawBullets();
};


#endif //SHOOTER_WEAPON_H
