#pragma once
#include "InstructionsState.h"
#include "MenuState.h"

InstructionsState::InstructionsState()
{

}

InstructionsState::~InstructionsState()
{
}

void InstructionsState::HandleEvents(Game& game)
{
	auto& inputManager = InputManager::Instance();
	Event ev;
	while (inputManager.HasEvent(&ev)) {
		if (inputManager.IsQuit(ev))
			game.Quit();
		else if (inputManager.IsMouseClicked(ev))
		{
			if (ev.GetEventValue().button.x > _backButton.getX1() && ev.GetEventValue().button.x < _backButton.getX2() && ev.GetEventValue().button.y > _backButton.getY1() && ev.GetEventValue().button.y < _backButton.getY2()) {
				//Back to menu
				auto state = std::make_unique<MenuState>();
				game.ChangeState(std::move(state));
			}
		}
	}
}

void InstructionsState::Update(Game & game, float time)
{
}

void InstructionsState::Draw(Game & game)
{
	RenderManager::Instance().DrawTexture(_background->GetTexture(), NULL, NULL);
	RenderManager::Instance().DrawText("First person shooter", config::width / 2 - 250, config::height / 3 - 170, 160, 40);
	//RenderManager::Instance().DrawText("Kill all the enemies to win the game", config::width / 2 - 250, config::height / 3 - 120, 160, 40);
	RenderManager::Instance().DrawText("Controls: ", config::width / 2 - 250, config::height / 3 - 100, 160, 25);
	RenderManager::Instance().DrawText("Moving: W,A,S & D ", config::width / 2 - 250, config::height / 3 - 60, 160, 25);
	RenderManager::Instance().DrawText("Aiming: Mouse move", config::width / 2 - 250, config::height / 3 - 20, 160, 25);
	RenderManager::Instance().DrawText("Shooting: Left Mouse button", config::width / 2 - 250, config::height / 3 + 20, 160, 25);
	RenderManager::Instance().DrawText("Pause: Esc Button", config::width / 2 - 250, config::height / 3 + 60, 160, 25);

	_backButton.drawButton();
}

void InstructionsState::Init()
{
	_background = std::make_unique<Texture>(AssetManager::Instance().LoadTexture("menu-wallpaper"));
	_backButton = Button("button_back", (config::width / 2) - 150, 800, 300, 50);
}