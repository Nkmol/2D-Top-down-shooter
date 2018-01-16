//
// Created by Mevlüt Özdemir on 29-11-17.
//

#ifndef SHOOTER_SHOTGUN_H
#define SHOOTER_SHOTGUN_H


#include <Weapon.h>

class Shotgun : public Weapon {
	int _number = 500;
public:
    Shotgun(int _damage = 40, float fireRate = 0.5);
	std::vector<Bullet> GetBullet(int angle, Point coordinates, bool & isCheatActive);
};


#endif //SHOOTER_SHOTGUN_H
