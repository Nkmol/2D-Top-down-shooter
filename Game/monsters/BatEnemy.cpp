//
// Created by Ahmad Rahimi on 11/29/17.
//

#include "BatEnemy.h"
namespace Properties {
    const float attrSpeed = 260.0f;
    const int attrDmg = 5;
    const int attrLp = 15;
    const int attrReward = 5;
    const int weightMultiplier = 10;
}
BatEnemy::BatEnemy(const Point &coordinates, bool isLeader) : EnemyBase("batenemy", coordinates, Properties::attrSpeed, isLeader, Properties::attrDmg,
                                                                        Properties::attrLp, Properties::attrReward) {
    this->weightMultiplier = Properties::weightMultiplier;
}

void BatEnemy::update(float time) {
    EnemyBase::update(time);
    if(this->currentUpdateCounter % 50 == 0) {
        this->weightMultiplier = rand() % 100 + 10;
    }
}

void BatEnemy::goTarget() {
    if(this->currentUpdateCounter >= this->maxUpdateCounter){
        this->currentUpdateCounter = 0;
        attackTarget = !attackTarget;
        this->maxUpdateCounter = attackTarget ? rand() % 75 + 50 : rand() % 60 + 30;
        if(!attackTarget) {
            int rAngle = rand() % 360 + 1;
            float targetX = this->GetCoordinates().x + float(200 * cos(rAngle));
            float targetY = this->GetCoordinates().y + float(200 * sin(rAngle));
            this->destinationPoint = Point(targetX, targetY);
        }
    }else{
        this->currentUpdateCounter++;
    }

    if(attackTarget){
        EnemyBase::goTarget();
    }
}