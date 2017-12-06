#include "PausedState.h"
#include "RenderManager.h"
#include "Config.h"
#include "Level.h"
#include "Game.h"
#include "InputManager.h"

PausedState::PausedState()
{
}

PausedState::~PausedState()
{
}

void PausedState::HandleEvents(Game & game)
{
	auto &inputManager = InputManager::instance();

	SDL_Event event{};

	while (inputManager.hasEvent(&event)) 
	{
		if (inputManager.isPauseResume(event))
		{
			game.PopState();
		}
		if (inputManager.isQuit(event)) {
			game.Quit();
		}
	}
}

void PausedState::Update(Game & game, float time)
{
}

void PausedState::Draw(Game & game)
{
	MapManager::Instance().Render();
	game.GetLevel()->Draw();
	RenderManager::Instance().DrawText("Press ESC to resume game", config::width/2 - 155, config::height/2 - 20, 360, 40, 0);
}

void PausedState::Init()
{
}
