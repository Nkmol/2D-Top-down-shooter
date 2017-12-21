#include "PlayingState.h"
#include "PausedState.h"
#include "Game.h"
#include "Level.h"
#include "InputManager.h"
#include "StateGameOver.h"

PlayingState::PlayingState() : PlayingState(0, "")
{
}

PlayingState::PlayingState(const int level, const std::string& savedGame) : _level(Level{ level, savedGame }) {
}


PlayingState::~PlayingState() = default;

void PlayingState::HandleEvents(Game &game) {
    auto &inputManager = InputManager::Instance();

	Event event;
    if(inputManager.IsMousePressed(event)){
        _level.HandleEvents(event);
    }

    while (inputManager.HasEvent(&event)) {
        if (inputManager.IsPauseResume(event)) {
            auto state = std::make_unique<PausedState>();
            game.ChangeState(std::move(state));
        }
        if (inputManager.IsQuit(event)) {
            game.Quit();
        }
        _level.HandleEvents(event);
    }
}

void PlayingState::Update(Game &game, float time) {
	if(_level.GetPlayer().GetState() == "dead")
	{
		game.ChangeState(make_unique<StateGameOver>());
		return;
	}

	_level.Update(time);
}

void PlayingState::Draw(Game &game) {
	MapManager::Instance().Render();
	_level.Draw();
}

void PlayingState::Init(Game& game)
{
}
