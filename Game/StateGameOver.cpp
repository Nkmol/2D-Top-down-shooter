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

	RenderManager::Instance().DrawText("Game Over", config::width / 2 - 360/2, config::height / 2 - 40/2,
		360, 40, 0, 227, 20, 20);
	RenderManager::Instance().DrawText("Press any button to return to main menu...", config::width / 2 - 200, config::height - 100 - 20,
		200, 20);
}
