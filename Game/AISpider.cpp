//
// Created by Ahmad Rahimi on 1/16/18.
//

#include "AISpider.h"

void AISpider::Update(float time)
{
    AIDefault::Update(time);
}

void AISpider::GoTarget()
{
    _owner->hasAnimation = true;
    if (this->restTimer.GetTimePassed() >= attackTime && _attackTarget)
    {
        _attackTarget = !_attackTarget;
        restTimer = Timer();
        _owner->SetSpriteToken("spider");
        _owner->ChangeState("stop");
        _owner->SetFrames(0);
    }else if (this->restTimer.GetTimePassed() >= restTime && !_attackTarget){
        restTimer = Timer();
        _owner->SetSpriteToken("spider");
        _owner->ChangeState("walk");
        _owner->SetFrames(6);
        _owner->SetAnimationTimer(0.05f);
        _attackTarget = !_attackTarget;
    }

    if(_attackTarget)
    {
        Point p = Point(_owner->_player->GetMidX() - (_owner->GetWidth()/2), _owner->_player->GetMidY() - (_owner->GetHeight()/2));
        _owner->SetDestinationPoint(p);
        doMove = true;
    }else{
        doMove = false;
    }
}

std::unique_ptr<IAIBase> AISpider::Clone() const
{
    return make_unique<AISpider>(static_cast<AISpider const &>(*this));
}
