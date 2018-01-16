#include "StateGameOver.h"
#include "Event.h"
#include "InputManager.h"
#include "Game.h"
#include "Config.h"
#include "../Engine/UIText.h"
#include "Hud.h"


StateGameOver::StateGameOver()
{
	auto conti =  std::make_unique<UIText>(UIText("Press any button to return to main menu...", 24, { config::width / 2 - 200, config::height - 100 - 20 }));
	Hud::Instance().AddComponent("ContinueGameover", std::move(conti));
	auto title = std::make_unique<UIText>(UIText("Game over", 72));
	title->Center();
	Hud::Instance().AddComponent("TitelGameover", std::move(title));
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
}
