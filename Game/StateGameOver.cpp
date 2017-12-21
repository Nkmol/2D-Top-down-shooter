#include "StateGameOver.h"
#include "Event.h"
#include "InputManager.h"
#include "Game.h"
#include "Config.h"
#include "../Engine/UIText.h"


StateGameOver::StateGameOver()
{
}


StateGameOver::~StateGameOver()
{
}

void StateGameOver::Init(Game& game)
{
	_UITitle = UIText("Game over", 72);
	_UITitle.Center();

	_UIContinue = UIText("Press any button to return to main menu...", 24, { config::width / 2 - 200, config::height - 100 - 20 });
}

void StateGameOver::HandleEvents(Game& game, Event& event)
{
	auto& inputManager = InputManager::Instance();

	// If any key is pressed
	if (inputManager.IsKeyDown(event))
	{
		game.PopState(2);
	}
}

void StateGameOver::Update(Game& game, float time)
{
}

void StateGameOver::Draw(Game& game)
{
	// Draw previous state (the game)
	game.GetStateBack(1)->Draw(game);

	_UITitle.Draw();
	_UIContinue.Draw();
}
