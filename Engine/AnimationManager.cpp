//
// Created by Mevlüt Özdemir on 08-12-17.
//
#include "AnimationManager.h"

AnimationManager *AnimationManager::sInstance = nullptr;

AnimationManager::AnimationManager() = default;

AnimationManager &AnimationManager::Instance() {
    static AnimationManager sInstance;

    return sInstance;
}

void AnimationManager::update(MoveableObject &object, double time) {

    object.DecreaseAnimationTimer(time);

    if (object.IsReadyForAnimation()) {
        int nextSprite = object.GetNextSpriteIndex();

        if (object.IsAnimationFinished()) {
            object.HandleAnimationFinished();
            return;
        }

        auto token = GenerateToken(object, nextSprite);
        object.ChangeSprite(token);
        object.ResetAnimationTimer();
    }
}

// Creates a token like: soldier/handgun/idle/0
string AnimationManager::GenerateToken(MoveableObject &object, const int sprite) const {
    auto token = object.getAnimationToken();    // eg: soldier/handgun
    token.append("/");
    token.append(object.GetState());            // eg: soldier/handgun/idle
    token.append("/");
    return token.append(to_string(sprite));     // eg: soldier/handgun/idle/0
}


void AnimationManager::addGameObjects(vector<shared_ptr<MoveableObject>> &objects) {
    this->_objs = objects;
}
