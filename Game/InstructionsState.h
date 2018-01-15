#pragma once

#include "State.h"
#include "Config.h"
#include "InputManager.h"
#include "Game.h"
#include "Button.h"
#include "MenuState.h"
#include "../Engine/UIText.h"
#include "../Engine/UIIcon.h"

class InstructionsState : public State {
public:
	InstructionsState();

	~InstructionsState();

	void HandleEvents(Game &game, Event &ev) override;

	void Update(Game &game, float time) override;

	void Draw(Game &game) override;

	void Init(Game& game) override;

private:

	std::vector<unique_ptr<Button>> _buttons;
	std::unique_ptr<Texture> _background;
	std::vector<UIText> _texts;
	std::unique_ptr<UIIcon> _miniBackground;
};
