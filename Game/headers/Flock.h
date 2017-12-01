//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_FLOCK_H
#define SHOOTER_FLOCK_H


#include "EnemyBase.h"
#include "memory"
#include "vector"

class Flock {
    shared_ptr<EnemyBase> leader;
    std::vector<EnemyBase> members;
    std::map<string, std::vector<EnemyBase>> quadtree;

public:
    explicit Flock(shared_ptr<EnemyBase> leader);

    void addMember(EnemyBase newMember);
    void removeFarMembers();
    void update(float time);
    string placeEnemyAtQuadrant(EnemyBase& replaceEnemy);
    void draw();

    int mapH;
    int mapW;
};


#endif //SHOOTER_FLOCK_H
