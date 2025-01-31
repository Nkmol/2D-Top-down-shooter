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

    static InputManager *_instance;

    int _mousePositionX, _mousePositionY;

    std::map<SDL_Keycode, Point> _keyDirections;

    InputManager();

    bool _buttonState;

public:
    InputManager(InputManager const &) = delete;

    void operator=(InputManager const &) = delete;

    static InputManager &Instance();

    bool HasEvent(Event *event);

    bool IsKeyDown(Event &event);

    Point GetDirection(Event &event);

    bool IsMouseMoved(Event &event);

    bool IsMousePressed(Event &event);

    int GetMousePositionX() const;

    int GetMousePositionY() const;

    int CalculateMouseAngle(MoveableObject &object);

    int RecalculateMouseAngle(MoveableObject &object);

    bool IsKeyUp(Event &event);

    bool IsQuit(Event &event);

    bool IsPauseResume(Event &event);

    bool IsNumericKeyPressed(Event &event, int &key);

    const bool IsKeyDown(Event &event, const std::string name) const;

    bool IsMouseReleased(Event &event);

    void HandleMouseReleased();

    bool IsMouseClicked(Event &event);

	const bool& LMBState() const { return _buttonState; }
};


#endif //SHOOTER_INPUTMANAGER_H
