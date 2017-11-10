//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <iostream>
#include "headers/InputManager.h"
#include "headers/Direction.h"


InputManager *InputManager::sInstance = nullptr;

InputManager::InputManager() {
    InputManager::keyDirections = {
            {SDLK_w, Direction::Top},
            {SDLK_d, Direction::Right},
            {SDLK_s, Direction::Bottom},
            {SDLK_a, Direction::Left},
    };
}

InputManager *InputManager::instance() {
    if (sInstance == nullptr) {
        sInstance = new InputManager();
    }

    return sInstance;
}

bool InputManager::hasEvent(SDL_Event *event) {
    return static_cast<bool>(SDL_PollEvent(event));
}


bool InputManager::isKeyDown(SDL_Event &event) {
    return event.type == SDL_KEYDOWN;
}

Direction InputManager::getDirection(SDL_Event &event) {

    // TODO REFACTOR

    SDL_PumpEvents();

    // update keyboard state
    auto keysArray = const_cast <Uint8 *> (SDL_GetKeyboardState(new int(2)));

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

    if (keysArray[SDL_SCANCODE_W]) {
        return Direction::Top;
    }

    if (keysArray[SDL_SCANCODE_D]) {
        return Direction::Right;
    }

    if (keysArray[SDL_SCANCODE_S]) {
        return Direction::Bottom;
    }

    if (keysArray[SDL_SCANCODE_A]) {
        return Direction::Left;
    }


//    auto search = keyDirections.find(event.key.keysym.sym);
//
//    if (search != keyDirections.end()) {
//        return search->second; // search->first is the key.. search->second is the value..
//    }

    // if the key does not exists in the map. It is not a valid key.


    return Direction::Null;
}

