#pragma once

#include "Player.h"
#include "MoveableObject.h"
#include "GameObject.h"
#include "MapManager.h"
#include <vector>
#include <memory>
#include "FlockController.h"
#include <InputManager.h>
#include "Weapon.h"
#include "Uzi.h"
#include "monsters/ZombieEnemy.h"
#include "Handgun.h"
#include "Shotgun.h"
#include "Config.h"
#include "WaveController.h"
#include "Wave.h"
#include <json.hpp>
using json = nlohmann::json;

class Level {
    int _level;
	std::string _map;
    std::vector<shared_ptr<MoveableObject>> _objs;
    shared_ptr<std::vector<shared_ptr<MoveableObject>>> _npcs;
    std::vector<shared_ptr<GameObject>> _loot;
    shared_ptr<Player> _player;

	double _levelSpeed;
	FlockController _flockController;
	WaveController _waveController;

	std::vector<Wave> _waves;

public:
    explicit Level(int level);

    void Init();

    void HandleEvents(SDL_Event event);

    void Update(float time);

    void Draw();

	const int GetId() const { return _level; }
	void SetId(const int id) { _level = id; }
	void SetMap(const std::string map) { _map = map; }
	void SetWaves(const std::vector<Wave> waves) { _waves = waves; }
};

void from_json(const json& j, Level& value)
{
	value.SetId(j.at("id").get<int>());
	value.SetMap(j.at("map").get<std::string>());
	value.SetWaves(j.at("waves").get<std::vector<Wave>>());
}