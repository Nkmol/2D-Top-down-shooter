//
// Created by Mevlüt Özdemir on 08-12-17.
//

#include "AnimationManager.h"
#include "Animation.h"

AnimationManager *AnimationManager::sInstance = nullptr;

AnimationManager::AnimationManager() = default;

AnimationManager &AnimationManager::Instance() {
    static AnimationManager sInstance;

    return sInstance;
}

void AnimationManager::update(float time) {

    for (auto &object : _objs) {

//        // just working for the player/soldier
//        std::size_t found = object->getSpriteToken().find("soldier");
//        if (found != std::string::npos) {
//            auto &animation = object->GetAnimation();
//            animation.DecreaseTimer(time);
//
//            if (animation.IsReady()) {
//                int nextSprite = animation.GetNextSprite();
//
//                if (animation.IsFinished()) {
//                    animation.HandleFinished();
//                    continue;
//                }
//
//                auto token = this->GenerateToken(animation, nextSprite);
//                object->ChangeSprite(token);
//
//                cout << token << endl;
//                animation.SetAnimationTimer(0.1f); // todo: fix
//            }
//        }
    }

}

// Creates a token like: soldier-rifle-idle-0
// GetAnimationToken = soldier-rifle
// GetState = idle
// sprite = 0
//string AnimationManager::GenerateToken(Animation &animation, const int sprite) const {
//    auto token = animation.GetAnimationToken() + "-" + animation.GetState() + "-";
//    return token.append(to_string(sprite));
//}


void AnimationManager::addGameObjects(vector<shared_ptr<MoveableObject>> &objects) {
    this->_objs = objects;
}
