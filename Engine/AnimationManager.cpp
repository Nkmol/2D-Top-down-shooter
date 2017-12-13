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

        if (object.IsAnimationFinished()) {
            object.HandleAnimationFinished();
            return;
        }

        auto token = GenerateToken(object);
        object.ChangeSprite(token);
        object.ResetAnimationTimer();
    }
}

// Creates a token like: soldier/handgun/idle/0
string AnimationManager::GenerateToken(MoveableObject &object) const {
    auto token = object.GetAnimationToken();                        // eg: soldier/handgun
    token.append("/");
    token.append(object.GetState());                                // eg: soldier/handgun/idle
    token.append("/");
    int nextSpriteIndex = object.GetNextSpriteIndex();              // eg: 0
    return token.append(to_string(nextSpriteIndex));                // eg: soldier/handgun/idle/0
}


