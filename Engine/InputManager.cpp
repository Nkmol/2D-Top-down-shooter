//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include <iostream>
#include <cmath>
#include "InputManager.h"
#include "MoveableObject.h"

InputManager *InputManager::sInstance = nullptr;

InputManager::InputManager() {
    InputManager::keyDirections = {
            { SDL_SCANCODE_W, Point::Up()},
            { SDL_SCANCODE_D, Point::Right() },
            { SDL_SCANCODE_S, Point::Down() },
            { SDL_SCANCODE_A, Point::Left() },
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

bool InputManager::isPauseResume(SDL_Event &event)
{
	return (event.key.keysym.sym == SDLK_ESCAPE && event.type == SDL_KEYDOWN);
}

Point InputManager::getDirection(SDL_Event& event) {
    // TODO REFACTOR, NEW CLASS

    SDL_PumpEvents();

	Point direction { 0, 0 };
    // update keyboard state
	const auto keysArray = SDL_GetKeyboardState(nullptr);

	for(auto const& value : keyDirections)
	{
		if (keysArray[value.first]) direction += value.second;
	}

	return direction;
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

	const auto& coordinates = object.GetCoordinates();
    float deltaY = coordinates.y - InputManager::getMousePositionY();
    float deltaX = coordinates.x - InputManager::getMousePositionX();

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
