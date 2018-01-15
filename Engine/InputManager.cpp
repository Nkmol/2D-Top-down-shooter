//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <iostream>
#include <cmath>
#include "InputManager.h"
#include "MoveableObject.h"

InputManager *InputManager::_instance = nullptr;

InputManager::InputManager() : _buttonState{false} {
    InputManager::_keyDirections = {
            {SDL_SCANCODE_W, Point::Up()},
            {SDL_SCANCODE_D, Point::Right()},
            {SDL_SCANCODE_S, Point::Down()},
            {SDL_SCANCODE_A, Point::Left()},
    };
}


InputManager &InputManager::Instance() {

    static InputManager _instance;

    return _instance;
}

bool InputManager::HasEvent(Event *event) {
    return static_cast<bool>(SDL_PollEvent(event->GetEvent()));
}

bool InputManager::IsKeyDown(Event &event) {
    return event.GetEventValue().type == SDL_KEYDOWN;
}

bool InputManager::IsKeyUp(Event &event) {
    return event.GetEventValue().type == SDL_KEYUP;
}

bool InputManager::IsQuit(Event &event) {
    return event.GetEventValue().type == SDL_QUIT;
}

bool InputManager::IsPauseResume(Event &event) {
    return (event.GetEventValue().key.keysym.sym == SDLK_ESCAPE && event.GetEventValue().type == SDL_KEYDOWN);
}

bool InputManager::IsNumericKeyPressed(Event &event, int &key) {
    std::map<SDL_Keycode, int> keyNumber = {
            {SDL_SCANCODE_1, 1},
            {SDL_SCANCODE_2, 2},
            {SDL_SCANCODE_3, 3},
            {SDL_SCANCODE_4, 4},
            {SDL_SCANCODE_5, 5},
    };

    const auto keysArray = SDL_GetKeyboardState(nullptr);

    for (auto const &value : keyNumber) {
        if (keysArray[value.first]) {
            key = value.second;
            return true;
        }
    }
    return false;
}

Point InputManager::GetDirection(Event &event) {
    // TODO REFACTOR, NEW CLASS

    SDL_PumpEvents();

    Point direction{0, 0};
    // update keyboard state
    const auto keysArray = SDL_GetKeyboardState(nullptr);

    for (auto const &value : _keyDirections) {
        if (keysArray[value.first])
            direction += value.second;
    }

    return direction;
}


// used this function when the mouse has been moved. (see: isMouseMoved function)
int InputManager::RecalculateMouseAngle(MoveableObject &object) {
    int mouseX, mouseY;

    SDL_GetMouseState(&mouseX, &mouseY);

    _mousePositionX = mouseX;
    _mousePositionY = mouseY;

    return CalculateMouseAngle(object);
}


// used to calculate. Call this method directly if mouse position is NOT changed
// (see: isMouseMoved function) so that we don't need to ask SDL for the current mouse coordinates
int InputManager::CalculateMouseAngle(MoveableObject &object) {

    float deltaY = object.GetMidY() - InputManager::GetMousePositionY();
    float deltaX = object.GetMidX() - InputManager::GetMousePositionX();

    double radian = atan2(deltaY, deltaX);

    auto result = static_cast<int>(radian * 180 / M_PI);
    return (result + 360) % 360;
}

bool InputManager::IsMouseMoved(Event &event) {
    return event.GetEventValue().type == SDL_MOUSEMOTION;
}

bool InputManager::IsMouseClicked(Event &event) {
    return event.GetEventValue().type == SDL_MOUSEBUTTONDOWN;
}

bool InputManager::IsMousePressed(Event &event) {
    if (IsMouseClicked(event)) {
        _buttonState = true;
    }

    return _buttonState;
}

bool InputManager::IsMouseReleased(Event &event) {
    return event.GetEventValue().type == SDL_MOUSEBUTTONUP;
}

void InputManager::HandleMouseReleased() {
    _buttonState = false;
}


const bool InputManager::IsKeyDown(Event &event, const std::string name) const {
    return event.GetEventValue().button.button == SDL_GetScancodeFromName(name.c_str());
}

// Getters & Setters

int InputManager::GetMousePositionX() const {
    return _mousePositionX;
}

int InputManager::GetMousePositionY() const {
    return _mousePositionY;
}
