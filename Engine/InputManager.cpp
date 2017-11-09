//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <iostream>
#include "headers/InputManager.h"
#include "headers/Direction.h"


InputManager *InputManager::sInstance = 0;

InputManager::InputManager() {
    InputManager::keyDirections = {
            {SDLK_w, Direction::Top},
            {SDLK_d, Direction::Right},
            {SDLK_s, Direction::Bottom},
            {SDLK_a, Direction::Left},
    };
}

InputManager *InputManager::instance() {
    if (sInstance == 0) {
        sInstance = new InputManager();
    }

    return sInstance;
}

bool InputManager::hasEvent(SDL_Event *event) {
    return SDL_PollEvent(event);
}


bool InputManager::isKeyDown(SDL_Event &event) {
    return event.type == SDL_KEYDOWN;
}

Direction InputManager::getKey(SDL_Event &event) {
    auto search = keyDirections.find(event.key.keysym.sym);

    if (search != keyDirections.end()) {
        return search->second; // search->second means the value.. search->first is the key
    }

    // if the key does not exists in the map. It is not a valid key.
    return Direction::Null;
}


void InputManager::beginNewFrame() {
    this->_pressedKeys.clear();
    this->_releasedKeys.clear();
    this->_mousePressedButtons.clear();
    this->_mouseReleasedButtons.clear();
}

void InputManager::keyDownEvent(const SDL_Event &event) {
    this->_pressedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = true;
}

void InputManager::keyUpEvent(const SDL_Event &event) {
    this->_releasedKeys[event.key.keysym.scancode] = true;
    this->_heldKeys[event.key.keysym.scancode] = false;
}

void InputManager::mouseDownEvent(const SDL_Event &event) {
    this->_mousePressedButtons[event.button.button] = true;
    this->_mouseHeldButtons[event.button.button] = true;
}

void InputManager::mouseUpEvent(const SDL_Event &event) {
    this->_mouseReleasedButtons[event.button.button] = true;
    this->_mouseHeldButtons[event.button.button] = false;
}

void InputManager::mouseMovedEvent(const SDL_Event &event) {
    _mousePositionX = event.motion.x;
    _mousePositionY = event.motion.y;
}

bool InputManager::wasKeyPressed(SDL_Scancode key) {
    return this->_pressedKeys[key];
}

bool InputManager::wasKeyReleased(SDL_Scancode key) {
    return this->_releasedKeys[key];
}

bool InputManager::isKeyHeld(SDL_Scancode key) {
    return this->_heldKeys[key];
}

bool InputManager::wasMouseButtonPressed(Uint8 button) {
    return this->_mousePressedButtons[button];
}

bool InputManager::wasMouseButtonReleased(Uint8 button) {
    return this->_mouseReleasedButtons[button];
}

bool InputManager::isMouseButtonHeld(Uint8 button) {
    return this->_mouseHeldButtons[button];
}


