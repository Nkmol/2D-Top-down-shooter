//
// Created by Ahmad Rahimi on 11/29/17.
//

#include "ZombieEnemy.h"
namespace Properties {
    const float attrSpeed = 50.0f;
    const int attrDmg = 12;
    const int attrLp = 100;
    const int attrReward = 8;
    const int weightMultiplier = 100;
}
ZombieEnemy::ZombieEnemy(const Point &coordinates, bool isLeader) : EnemyBase("zombieenemy", coordinates, Properties::attrSpeed, isLeader, Properties::attrDmg,
                                                                              Properties::attrLp, Properties::attrReward) {
    this->weightMultiplier = Properties::weightMultiplier;
}
