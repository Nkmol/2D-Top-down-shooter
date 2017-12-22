#pragma once

#include "State.h"
#include "Button.h"
#include <vector>

class PausedState : public State {
public:
	PausedState();

	~PausedState();

	void HandleEvents(Game &game, Event& event) override;

	void Update(Game &game, float time) override;

	void Draw(Game &game) override;

	void Init(Game& game) override;

private:
	vector<unique_ptr<Button>> _buttons;
};

