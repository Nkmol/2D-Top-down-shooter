#include "PlayingState.h"
#include "PausedState.h"
#include "Game.h"
#include "Level.h"
#include "InputManager.h"
#include "StateGameOver.h"
#include "WinState.h"
#include "Event.h"
#include <chrono>

PlayingState::PlayingState() : PlayingState(0, "")
{
}

PlayingState::PlayingState(const int level, const std::string& savedGame) : _level(level, savedGame) {
}


PlayingState::~PlayingState() = default;

void PlayingState::HandleEvents(Game &game, Event& event) {
    auto &inputManager = InputManager::Instance();

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
		int highestLevel = _level.GetPlayer().GetHighestLevel();
		AssetManager::Instance().SaveJson(_level.GetPlayer(), _level.GetPlayer().GetSaveName());
		//game.PopState();
		game.GetStateBack(1)->SetHighestLevel(highestLevel);
		game.ChangeState(std::make_unique<WinState>());
		return;
	}

	if (_level.GetPlayer().GetState() == "dead")
	{
		// Save top 10 highscores on level 3
		if(_level.GetLevelNumber() == 3) {
			auto j = AssetManager::Instance().LoadJson("highscores.json");
			std::map<string, std::string> highscores;
			if(!j.is_null())
			{
				highscores = j.get<decltype(highscores)>();
			}

			auto& p = _level.GetPlayer();

			auto t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
			auto a = std::string(std::ctime(&t));

			//std::pair<std::string, std::string> tq (std::to_string(p.GetPoints()), a);
			highscores.emplace(std::to_string(p.GetPoints()), a);

			AssetManager::Instance().SaveJson(highscores, "highscores.json");
		}
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
