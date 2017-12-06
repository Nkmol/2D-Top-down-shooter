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
	std::string muteString = "mutebutton";
	std::string quitString = "quitbutton";
	const int SCREEN_WIDTH = config::width; 
	const int SCREEN_HEIGHT = config::height;
	int muted;
	Button newgamebutton;
	Button loadgamebutton;
	Button creditsbutton;
	Button mutebutton;
	Button quitbutton;
};
