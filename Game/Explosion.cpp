//
// Created by Mevlüt Özdemir on 13-12-17.
//

#include <functional>
#include "Explosion.h"

Explosion::Explosion(string state, int frames, float animationTimer)
        : MoveableObject("explosion", Point(), 0.1f) {

    this->_state = state;
    this->frames = frames;
    this->animationTimer = animationTimer;
}

void Explosion::SetPoint(Point &point) {
    this->_coordinates = point;
}

void Explosion::HandleAnimationFinished() {
    this->hide();
    this->frames = 0;
}
