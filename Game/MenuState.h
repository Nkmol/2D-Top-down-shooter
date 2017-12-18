#pragma once
#include <string>
#include "State.h"
#include "Config.h"
#include "Button.h"

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

	std::unique_ptr<SDL_Texture, CustomDeleter> _background;
};