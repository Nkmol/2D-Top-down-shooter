#pragma once

#include <vector>
#include <memory>
#include <SDL.h>
#include <forward_list>
#include <InputManager.h>
#include "WaveController.h"
#include "json.hpp"
#include "Explosion.h"

class Player;

class MoveableObject;

class GameObject;

class Wave;

class Event;

class Level {
    InputManager &inputManager;
    int _level;
    std::vector<std::shared_ptr<MoveableObject>> _objs;
    std::vector<std::shared_ptr<MoveableObject>> _objsNoEnemies;
    std::vector<std::shared_ptr<MoveableObject>> _npcs;
    std::vector<std::shared_ptr<GameObject>> _loot;
    std::shared_ptr<Player> _player;
    std::vector<Explosion> _explosion;
    std::string _map;

    std::string _savedGame;
    double _levelSpeed;
    WaveController _waveController;
    std::forward_list<Wave> _waves;

    void LoadLevel();

    void LoadPlayer();

public:
    explicit Level(int level, const std::string savedGame);

    void Init();

    void HandleEvents(Event event);

    void Update(float time);

    void Draw();

    const int GetId() const { return _level; }

    void SetId(const int id) { _level = id; }

    void SetMap(const std::string map) { _map = map; }

    void SetWaves(const std::forward_list<Wave> waves) { _waves = waves; }

    void RemoveHiddenObjects(std::vector<std::shared_ptr<MoveableObject>> &objects);

    void RemoveHiddenExplosionObjects(std::vector<Explosion> &objects);

    void AddExplosion(const Point &point);


    void HandleMouseEvents(Event &event);

    void HandleKeyboardEvents(Event &event);

};

void from_json(const nlohmann::json &j, Level &value);