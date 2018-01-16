#pragma once
#include "State.h"
#include "../Engine/UIText.h"

class WinState : public State
{
public:
	WinState();
	~WinState();
	void Init(Game& game) override;
	void HandleEvents(Game& game, Event& event) override;
	void Update(Game& game, float time) override;
	void Draw(Game& game) override;
};

