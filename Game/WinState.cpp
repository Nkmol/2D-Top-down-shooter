#include "WinState.h"
#include "Event.h"
#include "InputManager.h"
#include "Game.h"
#include "Config.h"
#include "../Engine/UIText.h"
#include "Hud.h"


WinState::WinState()
{
	Hud::Instance().AddComponent("Wintext", std::make_unique<UIText>(UIText("Winner winner chicken dinner", 72, { 150, 200 })));
	Hud::Instance().AddComponent("Continuetext", std::make_unique<UIText>(UIText("Press any button to return to main menu...", 24, { config::width / 2 - 250, config::height - 100 - 20 })));
}


WinState::~WinState()
{
	Hud::Instance().Get<UIText>("Wintext")->Destroy();
	Hud::Instance().Get<UIText>("Continuetext")->Destroy();
}

void WinState::Init(Game& game)
{
}

void WinState::HandleEvents(Game& game, Event& event)
{
	auto& inputManager = InputManager::Instance();

	// If any key is pressed
	if (inputManager.IsKeyDown(event))
	{
		game.PopState(2);
	}
}

void WinState::Update(Game& game, float time)
{
}

void WinState::Draw(Game& game)
{
	// Draw previous state (the game)
	game.GetStateBack(1)->Draw(game);
}
