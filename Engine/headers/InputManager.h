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

    int _mousePositionX;
    int _mousePositionY;
    std::map<SDL_Scancode, bool> _heldKeys;
    std::map<SDL_Scancode, bool> _pressedKeys;
    std::map<SDL_Scancode, bool> _releasedKeys;
    std::map<Uint8, bool> _mousePressedButtons;
    std::map<Uint8, bool> _mouseReleasedButtons;
    std::map<Uint8, bool> _mouseHeldButtons;

public:

    static InputManager *instance();

    bool hasEvent(SDL_Event *event);

    bool isKeyDown(SDL_Event &event);

    Direction getKey(SDL_Event &event);

    void beginNewFrame();

    void keyUpEvent(const SDL_Event &event);

    void keyDownEvent(const SDL_Event &event);

    void mouseDownEvent(const SDL_Event &event);

    void mouseUpEvent(const SDL_Event &event);

    void mouseMovedEvent(const SDL_Event &event);

    bool wasKeyPressed(SDL_Scancode key);

    bool wasKeyReleased(SDL_Scancode key);

    bool isKeyHeld(SDL_Scancode key);

    bool wasMouseButtonPressed(Uint8 button);

    bool wasMouseButtonReleased(Uint8 button);

    bool isMouseButtonHeld(Uint8 button);

};


#endif //SHOOTER_INPUTMANAGER_H
