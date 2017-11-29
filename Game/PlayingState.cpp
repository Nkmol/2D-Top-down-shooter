#include <Uzi.h>
#include "PlayingState.h"
#include "InputManager.h"
#include "PausedState.h"


PlayingState::PlayingState() {
}


PlayingState::~PlayingState() {
}

void PlayingState::HandleEvents(Game &game) {
    auto &inputManager = InputManager::instance();

    SDL_Event event{};

    if (inputManager.hasEvent(&event)) {

        if (inputManager.isPauseResume(event)) {
            auto state = make_unique<PausedState>();
            game.ChangeState(std::move(state));
        }
        if (inputManager.isQuit(event)) {
            game.Quit();
        }
        game.GetLevel()->HandleEvents(event);
    }
}

void PlayingState::Update(Game &game, float time) {
    game.GetLevel()->Update(time);

}

void PlayingState::Draw(Game &game) {
    game.GetLevel()->Draw();
    auto weaponName = game.GetLevel()->getPlayer()->getWeapon()->getName();
    auto totalBullets = game.GetLevel()->getPlayer()->getWeapon()->totalBullets();
    auto remainingBullets = totalBullets - game.GetLevel()->getPlayer()->getWeapon()->getShooted();
    RenderManager::Instance().DrawText("Weapon: " + weaponName, config::width - 360, 0, 360, 40, 0);
    RenderManager::Instance().DrawText("Bullets: " +
                                       to_string(remainingBullets) + "/" +
                                       to_string(totalBullets), config::width - 360, 40, 360, 40, 0);
}

void PlayingState::Init() {
}