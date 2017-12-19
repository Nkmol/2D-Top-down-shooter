#pragma once

#include "State.h"

class PausedState : public State {
public:
	PausedState();

	~PausedState();

	void HandleEvents(Game &game) override;

	void Update(Game &game, float time) override;

	void Draw(Game &game) override;

	void Init() override;
};

