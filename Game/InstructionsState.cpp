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
	//RenderManager::Instance().DrawTexture(_background->GetTexture(), NULL, NULL);
	//RenderManager::Instance().DrawText("First person shooter", config::width / 2 - 250, config::height / 3 - 170, 160, 40);
	////RenderManager::Instance().DrawText("Kill all the enemies to win the game", config::width / 2 - 250, config::height / 3 - 120, 160, 40);
	//RenderManager::Instance().DrawText("Controls: ", config::width / 2 - 250, config::height / 3 - 100, 160, 25);
	//RenderManager::Instance().DrawText("Moving: W,A,S & D ", config::width / 2 - 250, config::height / 3 - 50, 160, 25);
	//RenderManager::Instance().DrawText("Aiming: Mouse move", config::width / 2 - 250, config::height / 3 - 0, 160, 25);
	//RenderManager::Instance().DrawText("Shooting: Left Mouse button", config::width / 2 - 250, config::height / 3 + 50, 160, 25);
	//RenderManager::Instance().DrawText("Pause: Esc Button", config::width / 2 - 250, config::height / 3 + 100, 160, 25);

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





}