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
    auto midX = point.x - (width / 2);
    auto midY = point.y - (height / 2);
    this->_coordinates = Point(midX, midY);
}

void Explosion::HandleAnimationFinished() {
    this->frames = 0;
    this->hide();
}
