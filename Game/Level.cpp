#include "Level.h"
#include "monsters/BatEnemy.h"

Level::Level(const int level) : _level(level), _levelSpeed(1) {
    Init();
}

void Level::Init() {
	//json uitlezen
	std::ifstream i;
	i.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		i.open("../content/level1.json");
	}
	catch (const ifstream::failure&)
	{
		cout << "Exception opening/reading file" << endl;
		return;
	}
	json j;
	i >> j;

	// Explicit "from_json" so it used the same reference
	from_json(j, *this);

	//level init	
    MapManager::Instance().Init(_map);

    auto player = make_shared<Player>("soldier", config::width/2, config::height/2);
    player->addWeapons({Uzi(), Handgun(), Shotgun()});
    player->changeWeapon(0); // set weapon to Uzi

    _objs.emplace_back(player);

    // save pointer seperate
    _player = player;
	_waveController.Init(_waves, _player, _npcs);
}

void Level::HandleEvents(SDL_Event event) {
    auto &inputManager = InputManager::instance();

    if (inputManager.isMouseMoved(event)) {
        // RECALCULATE players angle to mouse ONLY IF the mouse has been moved.
        int angle = inputManager.recalculateMouseAngle(*_player);

        // setAngle is called, so that the player aims towards the mouse, even when the player is not moving.
        _player->SetAngle(angle);
    }

    if (inputManager.isMouseClicked(event)) {
        auto bullet = make_shared<Bullet>(_player->shoot()); // returns a bullet
        _objs.emplace_back(bullet);
    }

    int key = 0;
    if (inputManager.isNumericKeyPressed(event, key)) {
        _player->changeWeapon(key-1);
    }

	if(inputManager.isKeyDown(event))
	{
		if(event.button.button == SDL_SCANCODE_LEFTBRACKET)
		{
			_levelSpeed -= .1;
			if (_levelSpeed < 0) _levelSpeed = 0;
		}
		else if(event.button.button == SDL_SCANCODE_RIGHTBRACKET)
		{
			_levelSpeed += .1;
		}
		else if(event.button.button == SDL_SCANCODE_F5)
		{
			// Quicksave prittified json
			std::ofstream o("../content/saves/quicksave.json"); // TODO refactor AssetManager
			o << std::setw(4) << json(*_player.get()) << std::endl;
		}
		else if(event.button.button == SDL_SCANCODE_F7)
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


    Point direction = inputManager.getDirection(event);

    int angle = inputManager.calculateMouseAngle(*_player);

    _player->SetAngle(angle);
    _player->Move(direction);
}

void Level::Update(float time) {
	const auto accSpeed = time *_levelSpeed;

    for (auto &&obj : _objs) {
        obj->update(accSpeed);
    }
	_waveController.Update(accSpeed);
}

void Level::Draw() {
    for (auto &&obj : _objs) {
        obj->draw();
    }
	_waveController.Draw();

    // TODO, verplaatsen
    auto weaponName = _player->getWeapon()->getName();
    auto totalBullets = _player->getWeapon()->totalBullets();
    auto remainingBullets = totalBullets - _player->getWeapon()->getShooted();
    RenderManager::Instance().DrawText("Weapon: " + weaponName, config::width - 360, 0, 360, 40, 0);
    RenderManager::Instance().DrawText("Bullets: " +
                                       to_string(remainingBullets) + "/" +
                                       to_string(totalBullets), config::width - 360, 40, 360, 40, 0);
}

void from_json(const json& j, Level& value)
{
	value.SetId(j.at("id").get<int>());
	value.SetMap(j.at("map").get<std::string>());
	value.SetWaves(j.at("waves").get<std::forward_list<Wave>>());
}
