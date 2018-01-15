#pragma once
#include "InstructionsState.h"

InstructionsState::InstructionsState()
{

}

InstructionsState::~InstructionsState()
{
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
	RenderManager::Instance().DrawTexture(_background->GetTexture(), NULL, NULL);

	_miniBackground->Draw();

	for (auto& t : _texts)
		t.Draw();

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
	_texts.push_back({ "Controls: ", 25,{ config::width / 2 - 120, config::height / 3 - 100 } });
	_texts.push_back({ "Moving: W, A, S & D ", 25,{ config::width / 2 - 120, config::height / 3 - 50 } });
	_texts.push_back({ "Aiming: Mouse move", 25,{ config::width / 2 - 120, config::height / 3 - 0 } });
	_texts.push_back({ "Shooting: LMB, Reload: R", 25,{ config::width / 2 - 120, config::height / 3 + 50 } });
	_texts.push_back({ "Pause: Esc Button", 25,{ config::width / 2 - 120, config::height / 3 + 100 } });
	_texts.push_back({ "Cheats: K = cheats, N = nuke", 25, {config::width / 2 - 120, config::height / 3 + 150} });
	_texts.push_back({ "Level speed: slower = [ faster = ]", 25, {config::width / 2 - 120, config::height / 3 + 200} });
}