//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_INPUTMANAGER_H
#define SHOOTER_INPUTMANAGER_H


#include <SDL_events.h>
#include <map>
#include "Direction.h"
#include "MoveableObject.h"

class InputManager {

/**
 * Singleton
 */

private:
    static InputManager *sInstance;

    int mousePositionX, mousePositionY;

    std::map<SDL_Keycode, Direction> keyDirections;

    InputManager();

public:

    static InputManager &instance();

    bool hasEvent(SDL_Event *event);

    bool isKeyDown(SDL_Event &event);

    Direction getDirection(SDL_Event &event);

    int getMouseAngleFrom(MoveableObject &object);
};


#endif //SHOOTER_INPUTMANAGER_H
