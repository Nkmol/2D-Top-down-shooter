//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_INPUTMANAGER_H
#define SHOOTER_INPUTMANAGER_H


#include <SDL_events.h>
#include <map>
#include "Direction.h"

class InputManager {

/**
 * Singleton
 */

private:
    static InputManager *sInstance;

    std::map<SDL_Keycode, Direction> keyDirections;

    InputManager();

public:

    static InputManager *instance();

    bool hasEvent(SDL_Event *event);

    bool isKeyDown(SDL_Event &event);

    Direction getDirection(SDL_Event &event);
};


#endif //SHOOTER_INPUTMANAGER_H
