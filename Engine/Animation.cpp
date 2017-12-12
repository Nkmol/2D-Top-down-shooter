//
// Created by Mevlüt Özdemir on 11-12-17.
//

#include "Animation.h"

Animation::Animation() {
    this->animationTime = 1000;
}

Animation::Animation(float time) {
    this->animationTime = time;
}

float Animation::GetAnimationTime() const {
    return animationTime;
}

bool Animation::ReadyToAnimate() const {
    return this->animationTime <= 0;
}



