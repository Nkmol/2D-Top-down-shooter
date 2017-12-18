#include "PausedState.h"
#include "RenderManager.h"
#include "Config.h"
#include "Level.h"
#include "Game.h"
#include "InputManager.h"
#include "Button.h"
#include "MenuState.h"

PausedState::PausedState()
{
}

PausedState::~PausedState()
{
}

void PausedState::HandleEvents(Game & game)
{
	auto &inputManager = InputManager::Instance();

	Event event;

	while (inputManager.HasEvent(&event)) 
	{
		if (inputManager.IsPauseResume(event))
		{
			game.PopState();
		}
		if (inputManager.IsQuit(event)) {
			game.Quit();
		}
		if(inputManager.IsMouseClicked(event))
		{
			// Check clicks on button
			for (auto& button : _buttons)
			{
				if (button->IsClicked(event)) button->Click();
			}
		}
	}
}

void PausedState::Update(Game & game, float time)
{
}

void PausedState::Draw(Game& game)
{
	MapManager::Instance().Render();
	game.GetStateBack(1)->Draw(game);
	RenderManager::Instance().DrawText("Press ESC to resume game", config::width/2 - 155, config::height/2 - 20, 360, 40);
	
	// Draw all buttons
	for (auto& button : _buttons)
	{
		button->draw();
	}
}

void PausedState::Init(Game& game)
{
	_buttons.emplace_back(make_unique<Button>("button_give-up", Point(config::width / 2 - 52, config::height / 4 ),Point( 114, 40 ), [&](){ 
		// Can only delete myself from outside
		// Set clears all states and sets a states
		game.SetState(make_unique<MenuState>());
	}));
}
