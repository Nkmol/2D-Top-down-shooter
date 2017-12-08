#pragma once
#include <string>
#include <memory>
#include "State.h"
#include "Config.h"
#include "Button.h"
#include "Texture.h"
#include <json.hpp>

class MenuSubState;
class Game;

class MenuState : public State
{
public:
	MenuState();
	~MenuState();

	void HandleEvents(Game& game) override;
	void Update(Game& game, float time) override;
	void Draw(Game& game) override;
	void Init() override;
	void ChangeState(std::unique_ptr<MenuSubState> substate);
private:

	std::string _muteString = "mutebutton";
	std::string _quitString = "quitbutton";
	int muted;

	Button _muteButton;
	Button _quitButton;
	std::unique_ptr<Texture> _background;
	std::vector<std::unique_ptr<MenuSubState>> _subStates;
};
