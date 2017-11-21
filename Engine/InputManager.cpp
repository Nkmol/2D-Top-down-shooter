//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <iostream>
#include <cmath>
#include "InputManager.h"
#include "Direction.h"
#include "MoveableObject.h"


InputManager *InputManager::sInstance = nullptr;

InputManager::InputManager() {
    InputManager::keyDirections = {
            {SDLK_w, Direction::Top},
            {SDLK_d, Direction::Right},
            {SDLK_s, Direction::Bottom},
            {SDLK_a, Direction::Left},
    };
}


InputManager &InputManager::instance() {
    static InputManager sInstance;

    return sInstance;
}

bool InputManager::hasEvent(SDL_Event *event) {
    return static_cast<bool>(SDL_PollEvent(event));
}

bool InputManager::isKeyDown(SDL_Event &event) {
    return event.type == SDL_KEYDOWN;
}

bool InputManager::isKeyUp(SDL_Event &event) {
    return event.type == SDL_KEYUP;
}

bool InputManager::isQuit(SDL_Event &event) {
    return event.type == SDL_QUIT;
}

Direction InputManager::getDirection(SDL_Event &event) {

    // TODO REFACTOR, NEW CLASS

    SDL_PumpEvents();

    // update keyboard state
    auto keysArray = SDL_GetKeyboardState(nullptr);

    if (keysArray[SDL_SCANCODE_W] && keysArray[SDL_SCANCODE_D]) {
        return Direction::TopRight;
    }

    if (keysArray[SDL_SCANCODE_W] && keysArray[SDL_SCANCODE_A]) {
        return Direction::TopLeft;
    }

    if (keysArray[SDL_SCANCODE_S] && keysArray[SDL_SCANCODE_D]) {
        return Direction::BottomRight;
    }

    if (keysArray[SDL_SCANCODE_S] && keysArray[SDL_SCANCODE_A]) {
        return Direction::BottomLeft;
    }

    // if not multiple keys are pressed, find the single key.
    auto search = keyDirections.find(event.key.keysym.sym);

    if (search != keyDirections.end()) {
        return search->second; // search->first is the key.. search->second is the value..
    }

    // When key doesn't exists in the map. It is not a valid key.

    return Direction::Null;
}


// used this function when the mouse has been moved. (see: isMouseMoved function)
int InputManager::recalculateMouseAngle(MoveableObject &object) {
    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    mousePositionX = mouseX;
    mousePositionY = mouseY;

    return calculateMouseAngle(object);
}

// used to calculate. Call this method directly if mouse position is NOT changed
// (see: isMouseMoved function) so that we don't need to ask SDL for the current mouse coordinates
int InputManager::calculateMouseAngle(MoveableObject &object) {

    float deltaY = object.getYPos() - InputManager::getMousePositionY();
    float deltaX = object.getXPos() - InputManager::getMousePositionX();

    double radian = atan2(deltaY, deltaX);

    auto result = static_cast<int>(radian * 180 / M_PI);
    return (result + 360) % 360;
}

bool InputManager::isMouseMoved(SDL_Event &event) {
    return event.type == SDL_MOUSEMOTION;
}

bool InputManager::isMouseClicked(SDL_Event &event) {
    return event.type == SDL_MOUSEBUTTONDOWN;
}


// Getters & Setters

int InputManager::getMousePositionX() const {
    return mousePositionX;
}

int InputManager::getMousePositionY() const {
    return mousePositionY;
}
