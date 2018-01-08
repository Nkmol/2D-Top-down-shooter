#pragma once
#include <string>
#include "State.h"
#include "Config.h"
#include "Button.h"
#include "../Engine/Texture.h"

class MenuState : public State
{
public:
	MenuState();
	~MenuState();

	void HandleEvents(Game& game, Event& event) override;
	void Update(Game& game, float time) override;
	void Draw(Game& game) override;
	void Init(Game& game) override;
	void StartLevel(const int level, Game& game);
	void SetRandomAd();
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
	Button _advertisement;

	std::vector<std::vector<std::string>> _advertisementsLinks;
	int _adnr;
	std::string _savedGame;

	std::unique_ptr<Texture> _background;
};
