#pragma once
#include "State.h"
#include "../Engine/Button.h"
#include <string>
#include <memory>
#include "Level.h"
#include "Player.h"
#include "InputManager.h"
#include <memory>
#include "PlayingState.h"
#include "MapManager.h"
#include "AudioManager.h"

class MenuState : public State
{
public:
	MenuState();
	~MenuState();

	void HandleEvents(Game& game) override;
	void Update(Game& game, float time) override;
	void Draw(Game& game) override;
	void Init() override;
private:
	std::string newgameString = "newgamebutton";
	std::string loadgameString = "loadgamebutton";
	std::string creditsString = "creditsbutton";
	const int SCREEN_WIDTH = 1500;
	const int SCREEN_HEIGHT = 960;
	Button newgamebutton;
	Button loadgamebutton;
	Button creditsbutton;
};
