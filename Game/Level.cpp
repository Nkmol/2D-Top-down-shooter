#include "Level.h"


Level::Level(const int level) : _level(level), _levelSpeed(1) {
    Init();
}

void Level::Init() {
    MapManager::Instance().Init("../content/map/space.tmx");
	PhysicsManager::Instance().setStaticObjects();
	PhysicsManager::Instance().setMoveableObjects(&_objsNoEnemies);

    auto player = make_shared<Player>("soldier", 100, 300);
    player->addWeapons({Uzi(), Handgun(), Shotgun()});
    player->changeWeapon(0); // set weapon to Uzi

    _objs.emplace_back(player);
    _objsNoEnemies.emplace_back(player);
    // save pointer seperate
    _player = player;

	_flockController.GenerateFlock<ZombieEnemy>(100, 250, 300, *_player, _objs);

    //_flockController.GenerateFlock<BatEnemy>(0, 200, 600, *_player);

}

void Level::HandleEvents(Event event) {
    auto &inputManager = InputManager::Instance();

    if (inputManager.IsMouseMoved(event)) {
        // RECALCULATE players angle to mouse ONLY IF the mouse has been moved.
        int angle = inputManager.RecalculateMouseAngle(*_player);

        // setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
        _player->SetAngle(angle);
    }

    if (inputManager.IsMouseClicked(event)) {
        auto bullet = make_shared<Bullet>(_player->shoot()); // returns a bullet
        _objsNoEnemies.emplace_back(bullet);
    }

    int key = 0;
    if (inputManager.IsNumericKeyPressed(event, key)) {
        _player->changeWeapon(key-1);
    }

	if(inputManager.IsKeyDown(event))
	{
		if (inputManager.IsKeyDown(event, "["))
		{
			_levelSpeed -= .1;
			if (_levelSpeed < 0) _levelSpeed = 0;
		}
		else if(inputManager.IsKeyDown(event, "]"))
		{
			_levelSpeed += .1;
		}
		else if(inputManager.IsKeyDown(event, "F5"))
		{
			// Quicksave prittified json
			std::ofstream o("../content/saves/quicksave.json"); // TODO refactor AssetManager
			o << std::setw(4) << json(*_player.get()) << std::endl;
		}
		else if(inputManager.IsKeyDown(event, "F7"))
		{
			// Quickload
			// TODO refactor AssetManager
			std::ifstream i;
			i.exceptions(ifstream::failbit | ifstream::badbit);
			try
			{
				i.open("../content/saves/quicksave.json");
			}
			catch (const ifstream::failure&)
			{
				cout << "Exception opening/reading file" << endl;
				return;
			}
			json j;
			i >> j;

			// Explicit "from_json" so it used the same reference
			from_json(j, *_player.get());
		}
	}


    Point direction = inputManager.GetDirection(event);

    int angle = inputManager.CalculateMouseAngle(*_player);

    _player->SetAngle(angle);
    _player->Move(direction);
}

void Level::Update(float time) {
    PhysicsManager::Instance().UpdateQuadTree(_objs);
	const auto accSpeed = time *_levelSpeed;

    for (auto &&obj : _objsNoEnemies) {
        obj->update(accSpeed);
    }
   // _player->update(time);

	auto iter(std::remove_if(_objsNoEnemies.begin(), _objsNoEnemies.end(), [](shared_ptr<MoveableObject> & o) { return !o->isVisible(); }));
	_objsNoEnemies.erase(iter, _objsNoEnemies.end());

    _flockController.UpdateFlocks(accSpeed);
}

void Level::Draw() {
    _player->draw();
    for (auto &&obj : _objsNoEnemies) {
        obj->draw();
    }
    _flockController.DrawFlocks();

    // TODO, verplaatsen
    auto weaponName = _player->getWeapon()->getName();
    auto totalBullets = _player->getWeapon()->totalBullets();
    auto remainingBullets = totalBullets - _player->getWeapon()->getShooted();
    RenderManager::Instance().DrawText("Weapon: " + weaponName, config::width - 360, 0, 360, 40, 0);
    RenderManager::Instance().DrawText("Bullets: " +
                                       to_string(remainingBullets) + "/" +
                                       to_string(totalBullets), config::width - 360, 40, 360, 40, 0);
// lines below this are only for debug purpose
    //PhysicsManager::Instance().DrawQTree();
}

