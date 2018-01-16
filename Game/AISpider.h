//
// Created by Ahmad Rahimi on 1/16/18.
//

#ifndef SHOOTER_AISPIDER_H
#define SHOOTER_AISPIDER_H


#include "AIDefault.h"

class AISpider : public AIDefault

{
    Timer restTimer = Timer();
    double attackTime = 5000;
    double restTime = 1000;
    bool _attackTarget = true;
public:
    using AIDefault::AIDefault;

    void Update(float time) override;
    void GoTarget() override;

    // TODO Make sure CRTP can use multiple levels of inheritance
    // This is a quick for this, but HelperClasses::CloneableBase should be resposible for this
    std::unique_ptr<IAIBase> Clone() const override;
};


#endif //SHOOTER_AISPIDER_H
