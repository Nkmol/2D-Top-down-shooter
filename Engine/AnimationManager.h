//
// Created by Mevlüt Özdemir on 08-12-17.
//

#ifndef SHOOTER_ANIMATIONMANAGER_H
#define SHOOTER_ANIMATIONMANAGER_H

#include <MoveableObject.h>
#include "AnimationManager.h"

class AnimationManager {

private:
    static AnimationManager *sInstance;

    AnimationManager();

public:
    // singleton
    static AnimationManager &Instance();

    void update(MoveableObject &object, double time);

    string GenerateToken(MoveableObject &object, const int sprite) const;
};


#endif //SHOOTER_ANIMATIONMANAGER_H
