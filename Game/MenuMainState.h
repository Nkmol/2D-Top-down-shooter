#pragma once
#include "MenuSubState.h"
#include <string>
#include <memory>
#include "Button.h"
#include "Event.h"

class MenuMainState : public MenuSubState
{
	std::string _newGameString = "newgamebutton";
	std::string _loadGameString = "loadgamebutton";
	std::string _creditsString = "creditsbutton";

	Button _newGameButton;
	Button _loadGameButton;
	Button _creditsButton;

public:
	MenuMainState();
	~MenuMainState();

	void HandleEvents(Game& game, MenuState& state, Event& ev) override;
	void Update(Game& game, float time) override;
	void Draw() override;
	void Init() override;
};