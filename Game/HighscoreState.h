#pragma once
#include "State.h"
#include "../Engine/UIIcon.h"
#include "Button.h"

class HighscoreState :  public State 
{
public:
	HighscoreState();
	~HighscoreState();
	void Init(Game& game) override;
	void HandleEvents(Game& game, Event& event) override;
	void Update(Game& game, float time) override;
	void Draw(Game& game) override;
private:
	std::vector<unique_ptr<Button>> _buttons;
	std::unique_ptr<Texture> _background;
	std::unique_ptr<UIIcon> _miniBackground;
	std::map<std::string, std::string> _highscores;
};

