//
// Created by Mevlüt Özdemir on 08-12-17.
//

#include <GameObject.h>
#include "AnimationManager.h"

AnimationManager *AnimationManager::sInstance = nullptr;

AnimationManager::AnimationManager() = default;

AnimationManager &AnimationManager::Instance() {
    static AnimationManager sInstance;

    return sInstance;
}

void AnimationManager::update(float time) {

    int frames = 19;

    for (auto &object : _objs) {
        std::size_t found = object->getSpriteToken().find("soldier");
        if (found != std::string::npos) {

            object->animationTimer -= time;
            if (object->animationTimer <= 0) {
                int index = object->getCurrentSprite() + 1;

                if (index > frames) {
                    index = 0;
                }

                object->setCurrentSprite(index);

                std::string token = "soldier-idle-0";
                token.append(to_string(object->getCurrentSprite()));
                object->changeSprite(token);
                cout << object->getSpriteToken() << endl;
                object->animationTimer = 0.1f;
            }
        }
    }
}


void AnimationManager::addGameObjects(vector<shared_ptr<MoveableObject>> &objects) {
    this->_objs = objects;
}
