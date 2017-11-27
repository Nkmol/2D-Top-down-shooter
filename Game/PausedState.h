#pragma once

#include "State.h"
#include "MoveableObject.h"
#include <memory>
#include <InputManager.h>


class PausedState : public State {
public:
	PausedState();

	~PausedState();

	void HandleEvents(Game &game) override;

	void Update(Game &game, float time) override;

	void Draw(Game &game) override;

	void Init() override;

private:
	// Todo might actually need to be GameObject
	// Use Pointer so Slicing will not occur
};

