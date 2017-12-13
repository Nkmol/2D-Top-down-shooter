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

    cout << object.GetSpriteToken() << endl;
    // just working for the player/soldier
    std::size_t found = object.GetSpriteToken().find("soldier");
    if (found != std::string::npos) {
        object.DecreaseAnimationTimer(time);

        if (object.IsReadyForAnimation()) {
            int nextSprite = object.GetNextSprite();

            if (object.AnimationFinished()) {
                object.HandleAnimationFinished();
            } else {
                auto token = this->GenerateToken(object, nextSprite);
                object.ChangeSprite(token);
                object.SetAnimationTimer(object.tempAnimationTimer); // todo: fix
            }

        }
    }

}

// Creates a token like: soldier-rifle-idle-0
// GetAnimationToken = soldier-rifle
// GetState = idle
// sprite = 0
string AnimationManager::GenerateToken(MoveableObject &object, const int sprite) const {
    auto token = object.getAnimationToken() + "-" + object.GetState() + "-";
    return token.append(to_string(sprite));
}


void AnimationManager::addGameObjects(vector<shared_ptr<MoveableObject>> &objects) {
    this->_objs = objects;
}
