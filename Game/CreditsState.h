#pragma once
#include <string>
#include "State.h"
#include "Config.h"
#include "Texture.h"
#include "InputManager.h"
#include "Game.h"
#include "Button.h"
#include "MenuState.h"

class CreditsState : public State
{
public:
	CreditsState();
	~CreditsState();

	void HandleEvents(Game& game) override;
	void Update(Game &game, float time) override;

	void Draw(Game &game) override;

	void Init() override;
private:
	std::unique_ptr<Texture> _background;
	Button _backButton;
};