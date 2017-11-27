#pragma once
#include "State.h"
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
private:
	Button newgamebutton;
	Button loadgamebutton;
	Button creditsbutton;
	const int SCREEN_WIDTH = 1500;
	const int SCREEN_HEIGHT = 960;
};
