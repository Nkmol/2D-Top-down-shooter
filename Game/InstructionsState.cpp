#pragma once
#include "InstructionsState.h"
#include "Hud.h"

InstructionsState::InstructionsState()
{

}

InstructionsState::~InstructionsState()
{
	// ...
	auto& hud = Hud::Instance();
	hud.Get<UIText>("Titel")->Destroy();
	hud.Get<UIText>("Moving")->Destroy();
	hud.Get<UIText>("Aiming")->Destroy();
	hud.Get<UIText>("Shooting")->Destroy();
	hud.Get<UIText>("Pause")->Destroy();
	hud.Get<UIText>("Cheats")->Destroy();
	hud.Get<UIText>("Speed")->Destroy();
}					

void InstructionsState::HandleEvents(Game& game, Event& ev)
{
	auto& inputManager = InputManager::Instance();
	
	if (inputManager.IsQuit(ev))
		game.Quit();
	if (inputManager.IsMouseClicked(ev))
	{
		// Check clicks on button
		for (auto& button : _buttons)
		{
			if (button->IsClicked(ev)) button->Click();
		}
	}
}

void InstructionsState::Update(Game & game, float time)
{
}

void InstructionsState::Draw(Game & game)
{
	RenderManager::Instance().DrawTexture(_background->GetPointer(), NULL, NULL);

	_miniBackground->Draw();

	// Draw all buttons
	for (auto& button : _buttons)
	{
		button->Draw();
	}
}

void InstructionsState::Init(Game& game)
{
	_background = AssetManager::Instance().LoadTexture("menu-wallpaper");
	_buttons.emplace_back(make_unique<Button>("button_back", Point((config::width / 2) - 150, 800), Point(300, 50), [&]() {
		// Can only delete myself from outside
		// Set clears all states and sets a states
		game.SetState(make_unique<MenuState>());
	}));

	_miniBackground = std::make_unique<UIIcon>(UIIcon("zwartkader", { config::width / 2 - 270, config::height / 3 - 180 }, 150));
	auto& hud = Hud::Instance();
	hud.AddComponent("Titel", make_unique<UIText>(UIText{ "Controls: ", 25,{ config::width / 2 - 120, config::height / 3 - 100 } }));
	hud.AddComponent("Moving", make_unique<UIText>(UIText{ "Moving: W, A, S & D ", 25,{ config::width / 2 - 120, config::height / 3 - 50 } }));
	hud.AddComponent("Aiming", make_unique<UIText>(UIText{ "Aiming: Mouse move", 25,{ config::width / 2 - 120, config::height / 3 - 0 } }));
	hud.AddComponent("Shooting", make_unique<UIText>(UIText{ "Shooting: LMB, Reload: R", 25,{ config::width / 2 - 120, config::height / 3 + 50 } }));
	hud.AddComponent("Pause", make_unique<UIText>(UIText{ "Pause: Esc Button", 25,{ config::width / 2 - 120, config::height / 3 + 100 } }));
	hud.AddComponent("Cheats", make_unique<UIText>(UIText{ "Cheats: K & N", 25, {config::width / 2 - 120, config::height / 3 + 150} }));
	hud.AddComponent("Speed", make_unique<UIText>(UIText{ "Change level speed: [ & ]", 25, {config::width / 2 - 120, config::height / 3 + 200} }));
}