#pragma once

#include <vector>
#include <memory>
#include <forward_list>
#include <json.hpp>

//engine
#include "MoveableObject.h"
#include "GameObject.h"
#include "MapManager.h"
#include "InputManager.h"

//game
#include "Player.h"
#include "FlockController.h"
#include "Weapon.h"
#include "Uzi.h"
#include "monsters/ZombieEnemy.h"
#include "Handgun.h"
#include "Shotgun.h"
#include "Config.h"
#include "WaveController.h"
#include "Wave.h"

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

	std::forward_list<Wave> _waves;

public:
    explicit Level(int level);

    void Init();

    void HandleEvents(SDL_Event event);

    void Update(float time);

    void Draw();

	const int GetId() const { return _level; }
	void SetId(const int id) { _level = id; }
	void SetMap(const std::string map) { _map = map; }
	void SetWaves(const std::forward_list<Wave> waves) { _waves = waves; }
};

void from_json(const json& j, Level& value);