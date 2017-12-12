//
// Created by Mevlüt Özdemir on 12-12-17.
//

#include "Animation.h"

Animation::Animation(): _token(), _frames(0), animationTimer(0)
{
}

Animation::Animation(string token, string state, float animationTimer) :
        _token{token}, _state{std::move(state)}, animationTimer{animationTimer} {

}

const string &Animation::GetState() const {
    return _state;
}

void Animation::SetState(const string &_state) {
    this->_state = _state;
    setCurrentSpriteIndex(-1);
}


void Animation::SetFrames(int _frames) {
    Animation::_frames = _frames;
}

void Animation::HandleFinished() {
    setCurrentSpriteIndex(-1);
}

float Animation::getAnimationTimer() const {
    return animationTimer;
}

void Animation::SetAnimationTimer(float animationTimer) {
    Animation::animationTimer = animationTimer;
}

void Animation::DecreaseTimer(float by) {
    Animation::animationTimer -= by;
}

bool Animation::IsReady() const {
    return getAnimationTimer() <= 0;
}


void Animation::setCurrentSpriteIndex(int index) {
    Animation::currentSprite = index;
}


int Animation::GetNextSprite() {
    return ++currentSprite;
}

string Animation::getToken() {
    return this->_token;
}

string Animation::GetAnimationToken() {
    return this->_token;
}

bool Animation::IsFinished() {
    return currentSprite >= _frames;
}



