//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_INPUTMANAGER_H
#define SHOOTER_INPUTMANAGER_H


#include <SDL_events.h>
#include <map>
#include "MoveableObject.h"
#include "Point.h"
#include "Event.h"

class InputManager {

/**
 * Singleton
 */

    static InputManager *sInstance;

    int mousePositionX, mousePositionY;

    std::map<SDL_Keycode, Point> keyDirections;

    InputManager();

public:
	InputManager(InputManager const&) = delete;
	void operator=(InputManager const&) = delete;

    static InputManager& Instance();

    bool HasEvent(Event *event);

    bool IsKeyDown(Event &event);

    Point GetDirection(Event &event);

    bool IsMouseMoved(Event &event);

    bool IsMouseClicked(Event &event);

    int GetMousePositionX() const;

    int GetMousePositionY() const;

    int CalculateMouseAngle(MoveableObject &object);

    int RecalculateMouseAngle(MoveableObject &object);

    bool IsKeyUp(Event &event);

    bool IsQuit(Event &event);

    bool IsPauseResume(Event &event);

    bool IsNumericKeyPressed(Event &event, int &key);

	const bool IsKeyDown(Event& event, const std::string name) const;
};


#endif //SHOOTER_INPUTMANAGER_H
