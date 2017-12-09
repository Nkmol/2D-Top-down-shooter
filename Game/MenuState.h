#pragma once
#include <string>
#include "State.h"
#include "Config.h"
#include "Button.h"
#include "Texture.h"

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
	std::string _newgameString = "newgamebutton";
	std::string _loadgameString = "loadgamebutton";
	std::string _creditsString = "creditsbutton";
	std::string _muteString = "mutebutton";
	std::string _quitString = "quitbutton";
	int _muted;
	Button _newgameButton;
	Button _loadgameButton;
	Button _creditsButton;
	Button _muteButton;
	Button _quitButton;
	std::unique_ptr<Texture> _background;
};