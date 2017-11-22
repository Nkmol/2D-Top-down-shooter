//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "FlockController.h"

void FlockController::generateFlock(int flockSize, int minPos, int maxPos, shared_ptr<Player> flockTarget,
                                    float flockSpeed) {
    shared_ptr<EnemyBase> leader{new EnemyBase("content/boid.png", rand() % maxPos + minPos, rand() % maxPos + minPos, flockSpeed, true)};
    leader->setTarget(flockTarget);

    shared_ptr<Flock> newFlock{new Flock(leader)};
    for(int i = 0; i < flockSize; i++){
        shared_ptr<EnemyBase> newFlockMember{new EnemyBase("content/boid.png", rand() % maxPos + minPos, rand() % maxPos + minPos, flockSpeed, false)};
        newFlock->addMember(newFlockMember);
    }
    this->flocks.push_back(newFlock);
}

void FlockController::drawFlocks() {
    for(auto const &flock: this->flocks){
        flock->draw();
    }
}

void FlockController::updateFlocks(float time) {
    for(auto const &flock: this->flocks){
        flock->update(time);
    }
}
