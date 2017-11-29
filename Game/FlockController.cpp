//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "FlockController.h"

using namespace std;
template<class T> void FlockController::generateFlock(int flockSize, int minPos, int maxPos, shared_ptr<Player> flockTarget) {
    shared_ptr<EnemyBase> leader{
            new T(Point(rand() % maxPos + minPos, rand() % maxPos + minPos), true)};
    leader->setTarget(flockTarget);

    shared_ptr<Flock> newFlock{new Flock(leader)};
    for (int i = 0; i < flockSize; i++) {
        shared_ptr<EnemyBase> newFlockMember{
                new T(Point(rand() % maxPos + minPos, rand() % maxPos + minPos), false)};
        newFlock->addMember(newFlockMember);
    }
    this->flocks.push_back(newFlock);
}
template void FlockController::generateFlock<ZombieEnemy>(int flockSize, int minPos, int maxPos, shared_ptr<Player> flockTarget);
template void FlockController::generateFlock<BatEnemy>(int flockSize, int minPos, int maxPos, shared_ptr<Player> flockTarget);

void FlockController::drawFlocks() {
    for (auto const &flock: this->flocks) {
        flock->draw();
    }
}

void FlockController::updateFlocks(float time) {
    for (auto const &flock: this->flocks) {
        flock->update(time);
    }
}
