//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_WEAPON_H
#define SHOOTER_WEAPON_H


#include <Bullet.h>
#include <vector>

class Weapon {

protected:
    std::vector<Bullet> bullets;

public:
    void shoot(int angle, float xPos, float yPos);

    void addBullets(const Bullet &bullet, int amount);

    void update(float time);

    void drawBullets();
};


#endif //SHOOTER_WEAPON_H
