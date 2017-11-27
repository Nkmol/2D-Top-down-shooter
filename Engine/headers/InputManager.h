//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_INPUTMANAGER_H
#define SHOOTER_INPUTMANAGER_H


#include <SDL_events.h>
#include <map>
#include "MoveableObject.h"
#include "Point.h"

class InputManager {

/**
 * Singleton
 */

    static InputManager *sInstance;

    int mousePositionX, mousePositionY;

    std::map<SDL_Keycode, Point> keyDirections;

    InputManager();

public:

    static InputManager &instance();

    bool hasEvent(SDL_Event *event);

    bool isKeyDown(SDL_Event &event);

	Point getDirection(SDL_Event& event);

    bool isMouseMoved(SDL_Event &event);

    bool isMouseClicked(SDL_Event &event);

    int getMousePositionX() const;

    int getMousePositionY() const;

    int calculateMouseAngle(MoveableObject &object);

    int recalculateMouseAngle(MoveableObject &object);

    bool isKeyUp(SDL_Event &event);

    bool isQuit(SDL_Event &event);

	bool isPauseResume(SDL_Event &event);
};


#endif //SHOOTER_INPUTMANAGER_H
