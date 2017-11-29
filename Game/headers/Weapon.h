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
    int shooted = 0;
    std::vector<Bullet> bullets;
    std::string name;

public:
    Weapon(int damage, std::string name);

    const vector<Bullet> &getBullets() const;

    void shoot(int angle, float xPos, float yPos);

    void addBullets(Bullet &bullet, int amount);

    void updateBullets(float time);

    void drawBullets();

    int totalBullets() const;

    int getShooted() const;

    std::string getName() const;
};


#endif //SHOOTER_WEAPON_H
