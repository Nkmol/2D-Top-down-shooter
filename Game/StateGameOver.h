#pragma once
#include "State.h"

class StateGameOver : public State
{
public:
	StateGameOver();
	~StateGameOver();
	void Init(Game& game) override;
	void HandleEvents(Game& game) override;
	void Update(Game& game, float time) override;
	void Draw(Game& game) override;
};

