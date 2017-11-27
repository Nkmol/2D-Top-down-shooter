#include "Level.h"

Level::Level(const int level) : _level(level)
{
	Init();
}

void Level::Init()
{
	MapManager::Instance().Init("../content/map/halflife.tmx");


	auto player = make_shared<Player>("soldier", 100, 300);
	auto uzi = make_unique<Weapon>(Uzi());
	player->addWeapon(*uzi);

	_objs.emplace_back(player);

	// save pointer seperate
	_player = player;
	_flockController.generateFlock(20, 100, 900, _player, 15.0f);
}

void Level::HandleEvents(SDL_Event event)
{	
	if (InputManager::instance().isMouseMoved(event)) {
		// RECALCULATE players angle to mouse ONLY IF the mouse has been moved.
		int angle = InputManager::instance().recalculateMouseAngle(*_player);

		// setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
		_player->setAngle(angle);
	}

	if (InputManager::instance().isKeyDown(event)) {
		Point direction = InputManager::instance().getDirection(event);

		int angle = InputManager::instance().calculateMouseAngle(*_player);

		_player->setAngle(angle);
		_player->Move(direction);
	}

	if (InputManager::instance().isKeyUp(event)) {
		_player->stopMove();
	}

	if (InputManager::instance().isMouseClicked(event)) {
		_player->shoot();
	}
}

void Level::Update(float time)
{
	for (auto &&obj : _objs) {
		obj->update(time);
	}
	_flockController.updateFlocks(time);
}

void Level::Draw()
{
	for (auto &&obj : _objs) {
		obj->draw();
	}
	_flockController.drawFlocks();
}
