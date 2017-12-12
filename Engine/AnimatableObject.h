//
// Created by Mevlüt Özdemir on 12-12-17.
//

#ifndef SHOOTER_ANIMATABLEOBJECT_H
#define SHOOTER_ANIMATABLEOBJECT_H

#include <string>

using namespace std;

class AnimatableObject {

private:
    string _state, _token;
    int _frames;
    float animationTimer;
    int currentSprite = 0;

public:
    AnimatableObject(string token, string state);

//    virtual string GetAnimationToken();
//
//    const string &GetState() const;
//
//    virtual void HandleAnimationFinished();
//
//    void SetFrames(int _frames);
//
//    void SetAnimationTimer(float animationTimer);
//
//    float GetAnimationTimer() const;
//
//    virtual void SetState(const string &_state);
//
//    bool IsReadyForAnimation() const;
//
//    void SetCurrentSpriteIndex(int index);
//
//    int GetNextSprite();
//
//    bool AnimationFinished();
//
//    void DecreaseAnimationTimer(float by);
};


#endif //SHOOTER_ANIMATABLEOBJECT_H
