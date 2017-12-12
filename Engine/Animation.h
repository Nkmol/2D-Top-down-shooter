//
// Created by Mevlüt Özdemir on 12-12-17.
//

#ifndef SHOOTER_ANIMATION_H
#define SHOOTER_ANIMATION_H

#include <string>

using namespace std;

class Animation {

private:
    std::string _token;
    std::string _state;
    int _frames;
    float animationTimer;
    int currentSprite = 0;

public:
    Animation();

    Animation(string _token, string _state, float animationTimer);

    string getToken();

    const string &GetState() const;

    void HandleFinished();

    void SetFrames(int _frames);

    void SetAnimationTimer(float animationTimer);

    float getAnimationTimer() const;

    virtual void SetState(const string &_state);

    bool IsReady() const;

    void setCurrentSpriteIndex(int index);

    int GetNextSprite();

    bool IsFinished();

    void DecreaseTimer(float by);

    string GetAnimationToken();
};


#endif //SHOOTER_ANIMATION_H
