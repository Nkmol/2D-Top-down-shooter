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
        // NextSpriteIndex() should be called BEFORE: IsAnimationFinished().
        // Because the function increases and returns the objects currentSpriteIndex;
        int nextSpriteIndex = object.NextSpriteIndex();

        if (object.IsAnimationFinished()) {
            object.HandleAnimationFinished();
            return;
        }

        auto token = GenerateToken(object, nextSpriteIndex);
        auto texture = GetTexture(token);

        object.ChangeTexture(*texture);
        object.ResetAnimationTimer();
    }
}

// Creates a token like: soldier/handgun/idle/0
string AnimationManager::GenerateToken(MoveableObject &object, int sprite) const {
    auto token = object.GetAnimationToken();               // eg: soldier/handgun
    token.append("/");
    token.append(object.GetState());                       // eg: soldier/handgun/idle
    token.append("/");
    return token.append(to_string(sprite));                // eg: soldier/handgun/idle/0
}

Texture *AnimationManager::GetTexture(std::string token) {
    auto it = textures.find(token);

    if (it != textures.end()) {
        // std::cout << "texture found" << std::endl;
        return it->second;
    } else {
        // std::cout << "texture not found" << std::endl;
        auto texture = AssetManager::Instance().LoadTexture(token).release();
        textures.insert(std::make_pair(token, texture));
        return texture;
    }
};

AnimationManager::~AnimationManager() {
    for (auto itr = textures.begin(); itr != textures.end(); itr++) {
        delete itr->second;
    }
}



