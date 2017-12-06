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
