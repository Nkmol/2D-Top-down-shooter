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
    std::vector<shared_ptr<EnemyBase>> members;
public:
    explicit Flock(shared_ptr<EnemyBase> leader);

    void addMember(shared_ptr<EnemyBase> newMember);
    void removeFarMembers();
    void update(float time);
    void draw();
};


#endif //SHOOTER_FLOCK_H
