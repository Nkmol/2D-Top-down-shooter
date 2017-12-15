//
// Created by Mevlüt Özdemir on 13-12-17.
//

#ifndef SHOOTER_EXPLOSION_H
#define SHOOTER_EXPLOSION_H


#include <MoveableObject.h>

class Explosion : public MoveableObject {

public:
    Explosion(string state, int frames, float animationTimer);

    void SetPoint(Point &point);

    void HandleAnimationFinished() override;
};


#endif //SHOOTER_EXPLOSION_H
