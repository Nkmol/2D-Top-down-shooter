#pragma once

#include <vector>
#include <memory>
#include <SDL.h>
#include <forward_list>
#include "WaveController.h"
#include "json.hpp"

class Player;
class MoveableObject;
class GameObject;
class Wave;
class Event;

class Level {
    int _level;
    std::vector<std::shared_ptr<GameObject>> _objs;
	std::vector<std::shared_ptr<MoveableObject>> _objsNoEnemies;
    std::vector<std::shared_ptr<MoveableObject>> _npcs;
    std::vector<std::shared_ptr<GameObject>> _loot;
	std::shared_ptr<Player> _player;
	std::string _map;


	double _levelSpeed;
	WaveController _waveController;

	std::forward_list<Wave> _waves;

public:
    explicit Level(int level);

    void Init();

    void HandleEvents(Event event);

    void Update(float time);

    void Draw();

	const int GetId() const { return _level; }
	void SetId(const int id) { _level = id; }
	void SetMap(const std::string map) { _map = map; }
	void SetWaves(const std::forward_list<Wave> waves) { _waves = waves; }
};

void from_json(const nlohmann::json& j, Level& value);