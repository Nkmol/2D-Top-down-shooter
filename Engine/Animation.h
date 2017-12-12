//
// Created by Mevlüt Özdemir on 11-12-17.
//

#ifndef SHOOTER_ANIMATION_H
#define SHOOTER_ANIMATION_H


#include <string>
#include <map>

class Animation {

protected:
    float animationTime;
    std::map<int, std::string> animationFrames;

public:
    Animation();

    Animation(float time);

    float GetAnimationTime() const;

    bool ReadyToAnimate() const;
};


#endif //SHOOTER_ANIMATION_H
