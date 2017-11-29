//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_FLOCKCONTROLLER_H
#define SHOOTER_FLOCKCONTROLLER_H


#include "Player.h"
#include "Flock.h"
#include "memory"
#include "vector"
#include "../monsters/ZombieEnemy.h"
class FlockController {
    shared_ptr<Player> target;
public:
    std::vector<shared_ptr<Flock>> flocks;
    FlockController() = default;
    template<class T> void generateFlock(int flockSize, int minPos, int maxPos, shared_ptr<Player> flockTarget);
    void drawFlocks();
    void updateFlocks(float time);
};

#endif //SHOOTER_FLOCKCONTROLLER_H
