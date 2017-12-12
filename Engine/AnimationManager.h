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

    std::vector<std::shared_ptr<MoveableObject>> _objs;
public:
    // singleton
    static AnimationManager &Instance();

    void update(float time);

    void addGameObjects(vector<shared_ptr<MoveableObject>> &objects);

    string GetToken(shared_ptr<MoveableObject> &object, const int sprite) const;
};


#endif //SHOOTER_ANIMATIONMANAGER_H
