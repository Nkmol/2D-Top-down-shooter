#include "PausedState.h"
#include "PlayingState.h"
#include "RenderManager.h"

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

	if (inputManager.hasEvent(&event)) 
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

void PausedState::Update(Game & game, int time)
{
}

void PausedState::Draw(Game & game)
{
	RenderManager::Instance().DrawText("Press ESC to resume game", config::width/2 - 155, config::height/2 - 20, 360, 40, 0);
}

void PausedState::Init()
{
}
