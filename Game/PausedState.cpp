#include "PausedState.h"
#include "PlayingState.h"

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
	}
}

void PausedState::Update(Game & game, int time)
{
}

void PausedState::Draw(Game & game)
{

}

void PausedState::Init()
{
}
