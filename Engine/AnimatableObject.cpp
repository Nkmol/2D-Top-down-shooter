//
// Created by Mevlüt Özdemir on 12-12-17.
//

#include "AnimatableObject.h"

AnimatableObject::AnimatableObject(){}

AnimatableObject::AnimatableObject(const string token, string state){}
//        :
//        _token{token},
//        _state{state},
//        currentSprite{-1} {}

//
//const string &AnimatableObject::GetState() const {
//    return _state;
//}
//
//void AnimatableObject::SetState(const string &_state) {
//    this->_state = _state;
//    SetCurrentSpriteIndex(-1);
//}
//
//
//void AnimatableObject::SetFrames(int _frames) {
//    AnimatableObject::_frames = _frames;
//}
//
//void AnimatableObject::HandleAnimationFinished() {
//    SetCurrentSpriteIndex(-1);
//}
//
//float AnimatableObject::GetAnimationTimer() const {
//    return animationTimer;
//}
//
//void AnimatableObject::SetAnimationTimer(float animationTimer) {
//    AnimatableObject::animationTimer = animationTimer;
//}
//
//void AnimatableObject::DecreaseAnimationTimer(float by) {
//    AnimatableObject::animationTimer -= by;
//}
//
//bool AnimatableObject::IsReadyForAnimation() const {
//    return GetAnimationTimer() <= 0;
//}
//
//
//void AnimatableObject::SetCurrentSpriteIndex(int index) {
//    AnimatableObject::currentSprite = index;
//}
//
//
//int AnimatableObject::GetNextSprite() {
//    return ++currentSprite;
//}
//
//string AnimatableObject::GetAnimationToken() {
//    return this->_token;
//}
//
//bool AnimatableObject::AnimationFinished() {
//    return currentSprite >= _frames;
//}
