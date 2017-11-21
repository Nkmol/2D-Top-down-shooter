#include "PlayingState.h"
#include "InputManager.h"


PlayingState::PlayingState()
{
}


PlayingState::~PlayingState()
{
}

void PlayingState::HandleEvents(Game& game)
{
	auto inputManager = InputManager::instance();
	SDL_Event event;

	if (inputManager.hasEvent(&event)) {

		// recalculate players angle to mouse ONLY IF the mouse has been moved.
		if (inputManager.isMouseMoved(event)) {
			int angle = inputManager.recalculateMouseAngle(*_player);

			// setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
			_player->setAngle(angle);
		}

		if (inputManager.isKeyDown(event)) {
			Direction direction = inputManager.getDirection(event);
			int angle = inputManager.calculateMouseAngle(*_player);
			_player->setAngle(angle);
			_player->move(direction);
		}

		if (inputManager.isKeyUp(event)) {
			_player->stopMove();
		}


		if (inputManager.isQuit(event)) {
			game.Quit();
		}
	}
}

void PlayingState::Update(Game& game, int time)
{
	// The reference & to the std::unique_ptr avoids the copying and you can use the uniqe_ptr without dereferencing.
	for (auto&& obj : _objs)
	{
		obj->update(time);
	}
	flockController.updateFlocks(time);
}

void PlayingState::Draw(Game& game)
{
	for (auto&& obj : _objs)
	{
		obj->draw();
	}
	flockController.drawFlocks();
}

void PlayingState::Init()
{
	shared_ptr<Player> player{new Player("../content/soldier.png", 100, 300)};

	_objs.emplace_back(player);

	// save pointer seperate
	_player = player;
	flockController.generateFlock(5,100,900,_player,0.3);
}
