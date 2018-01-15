#include "PlayingState.h"
#include "PausedState.h"
#include "Game.h"
#include "Level.h"
#include "InputManager.h"
#include "StateGameOver.h"
#include "Event.h"

PlayingState::PlayingState() : PlayingState(0, "")
{
}

PlayingState::PlayingState(const int level, const std::string& savedGame) : _level(level, savedGame) {
}


PlayingState::~PlayingState() = default;

void PlayingState::HandleEvents(Game &game, Event& event) {
    auto &inputManager = InputManager::Instance();

    if(inputManager.IsMousePressed(event)){
        _level.HandleEvents(event);
    }

	if (inputManager.IsPauseResume(event)) {
		auto state = std::make_unique<PausedState>();
		game.ChangeState(std::move(state));
	}

	_level.HandleEvents(event);
}

void PlayingState::Update(Game &game, float time) 
{	
	_level.Update(time);

	if (_level.IsCompleted())
	{
		AssetManager::Instance().SaveJson(this->_level.GetPlayer());
		game.PopState();
		return;
	}

	if (_level.GetPlayer().GetState() == "dead")
	{
		game.ChangeState(make_unique<StateGameOver>());
		return;
	}
}

void PlayingState::Draw(Game &game) {
	MapManager::Instance().Render();
	_level.Draw();
}

void PlayingState::Init(Game& game)
{
}
