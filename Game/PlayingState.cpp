#include "PlayingState.h"
#include "PausedState.h"
#include "Game.h"
#include "Level.h"
#include "InputManager.h"

PlayingState::PlayingState() {
}


PlayingState::~PlayingState() {
}

void PlayingState::HandleEvents(Game &game) {
    auto &inputManager = InputManager::Instance();

	Event event;

    while (inputManager.HasEvent(&event)) {

        if (inputManager.IsPauseResume(event)) {
            auto state = std::make_unique<PausedState>();
            game.ChangeState(std::move(state));
        }
        if (inputManager.IsQuit(event)) {
            game.Quit();
        }
        game.GetLevel()->HandleEvents(event);
    }
}

void PlayingState::Update(Game &game, float time) {
    game.GetLevel()->Update(time);

}

void PlayingState::Draw(Game &game) {
	MapManager::Instance().Render();
    game.GetLevel()->Draw();
}

void PlayingState::Init() {
}