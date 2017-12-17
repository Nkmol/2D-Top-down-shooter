#pragma once
#include <string>
#include "State.h"
#include "Config.h"
#include "Button.h"
#include "Texture.h"
#include "InputManager.h"
#include "PlayingState.h"
#include "InstructionsState.h"
#include "CreditsState.h"
#include "AudioManager.h"
#include "Game.h"
#include <experimental/filesystem>
#include "nfd.h"
#include <json.hpp>
#include <regex>

class MenuState : public State
{
public:
	MenuState();
	~MenuState();

	void HandleEvents(Game& game) override;
	void Update(Game& game, float time) override;
	void Draw(Game& game) override;
	void Init() override;
	void StartLevel(const int level, Game& game);
private:
	int _muted;
	int _highestLevel = 1;

	Button _newgameButton;
	Button _loadgameButton;
	Button _creditsButton;
	Button _instructions;
	Button _muteButton;
	Button _quitButton;
	Button _level1;
	Button _level2;
	Button _level3;

	std::string _savedGame;

	std::unique_ptr<Texture> _background;
};