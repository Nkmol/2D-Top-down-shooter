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

        if (inputManager.isMouseMoved(event)) {
            // RECALCULATE players angle to mouse ONLY IF the mouse has been moved.
            int angle = inputManager.recalculateMouseAngle(*_player);

            // setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
            _player->setAngle(angle);
        }

        if (inputManager.isKeyDown(event)) {
            Point direction = inputManager.getDirection(event);

            int angle = inputManager.calculateMouseAngle(*_player);

            _player->setAngle(angle);
            _player->Move(direction);
        }

        if (inputManager.isKeyUp(event)) {
            _player->stopMove();
        }

        if (inputManager.isMouseClicked(event)) {
            _player->shoot();
        }

        if (inputManager.isQuit(event)) {
            game.Quit();
        }
    }
}

void PlayingState::Update(Game& game, float time)
{
	// The reference & to the std::unique_ptr avoids the copying and you can use the uniqe_ptr without dereferencing.
	for (auto &&obj : _objs) {
		obj->update(time);
	}
	flockController.updateFlocks(time);
}

void PlayingState::Draw(Game &game) {
    for (auto &&obj : _objs) {
        obj->draw();
    }
    flockController.drawFlocks();
}

void PlayingState::Init() {
	auto player = make_shared<Player>("soldier", 100, 300);
	auto uzi = make_unique<Weapon>(Uzi());
    player->addWeapon(*uzi);

    _objs.emplace_back(player);

    // save pointer seperate
    _player = player;
    flockController.generateFlock(20, 100, 900, _player, 15.0f);
}