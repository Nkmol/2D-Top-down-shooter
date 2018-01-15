//
// Created by Mevlüt Özdemir on 08-12-17.
//
#include "AnimationManager.h"
#include "../Game/Explosion.h"

AnimationManager *AnimationManager::_instance = nullptr;

AnimationManager::AnimationManager() = default;

AnimationManager &AnimationManager::Instance() {
    static AnimationManager _instance;

    return _instance;
}

void AnimationManager::Update(MoveableObject &object, double time) {
    object.DecreaseAnimationTimer(time);

    if (object.IsReadyForAnimation()) {
        // NextSpriteIndex() should be called BECORE: IsAnimationFinished().
        // Because this func increases and returns the objects currenSpriteIndex;
        int nextSpriteIndex = object.NextSpriteIndex();

        if (object.IsAnimationFinished()) {
            object.HandleAnimationFinished();
            return;
        }

        auto token = GenerateToken(object, nextSpriteIndex);
        auto it = textures.find(token);

        if (it != textures.end()) {
            auto found = it->second;
//            object.ChangeTexture(it->second.get());
            std::cout << "found" << std::endl;
        } else {
            textures.insert(std::make_pair(token, AssetManager::Instance().LoadTexture(token)));
            object.ChangeSprite(token);
            std::cout << "not found" << std::endl;
        }

        object.ResetAnimationTimer();
    }
}

// Creates a token like: soldier/handgun/idle/0
string AnimationManager::GenerateToken(MoveableObject &object, int sprite) const {
    auto token = object.GetAnimationToken();                        // eg: soldier/handgun
    token.append("/");
    token.append(object.GetState());                                // eg: soldier/handgun/idle
    token.append("/");
    return token.append(to_string(sprite));                // eg: soldier/handgun/idle/0
}


