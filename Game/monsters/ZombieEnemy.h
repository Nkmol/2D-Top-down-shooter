//
// Created by Ahmad Rahimi on 11/29/17.
//

#ifndef SHOOTER_ZOMBIEENEMY_H
#define SHOOTER_ZOMBIEENEMY_H


#include <EnemyBase.h>

class ZombieEnemy : public EnemyBase{
public:
    ZombieEnemy(const Point &coordinates, bool isLeader);
};


#endif //SHOOTER_ZOMBIEENEMY_H
