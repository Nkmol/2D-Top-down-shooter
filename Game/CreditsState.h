#pragma once
#include "State.h"
#include "Config.h"
#include "InputManager.h"
#include "Game.h"
#include "Button.h"
#include "MenuState.h"
#include "../Engine/UIIcon.h"

class UIText;

class CreditsState : public State
{
public:
	CreditsState();
	~CreditsState();

	void HandleEvents(Game &game, Event& event) override;
	void Update(Game &game, float time) override;

	void Draw(Game &game) override;

	void Init(Game& game) override;
private:
	std::unique_ptr<Texture> _background;
	std::vector<unique_ptr<Button>> _buttons;
	std::unique_ptr<UIIcon> _miniBackground;
};