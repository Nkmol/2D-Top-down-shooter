#pragma once

#include <vector>
#include <memory>
#include <SDL.h>
#include <forward_list>
#include <InputManager.h>
#include "json.hpp"
#include "Explosion.h"
#include "WaveController.h"
#include "Wave.h"
#include "../Engine/UIText.h"
#include "TextComponent.h"


class EnemyBase;

class Player;

class MoveableObject;

class GameObject;

class Event;


class Level {
    int _level;
    std::vector<std::shared_ptr<MoveableObject>> _objsNoEnemies;
    std::vector<std::unique_ptr<EnemyBase>> _npcs;
    std::vector<std::shared_ptr<GameObject>> _loot;
    std::shared_ptr<Player> _player;
    std::vector<Explosion> _explosion;
    std::string _map;

    std::string _savedGame;
    double _levelSpeed;
    WaveController _waveController;
    std::forward_list<Wave> _waves;
	std::unique_ptr<UIText> _UIWeapon;
	std::unique_ptr<UIText> _UIBullets;

	void LoadLevel();

    void LoadPlayer();

	int count = 0;

	//std::unique_ptr<TextComponent> _weaponComponent;
	//std::shared_ptr<IHudComponent> _ammoComponent;

public:
    explicit Level(int level, const std::string savedGame);

    ~Level();

    void Init();

    void HandleEvents(Event event);

    void Update(float time);

    void Draw();

	const Player& GetPlayer() const;

    const int GetId() const { return _level; }

    void SetId(const int id) { _level = id; }

    void SetMap(const std::string map) { _map = map; }

    void SetWaves(const std::forward_list<Wave> waves) { _waves = waves; }

    void RemoveHiddenObjects(std::vector<std::shared_ptr<MoveableObject>> &_objects);

    void RemoveHiddenNpcs();

    void RemoveHiddenExplosionObjects(std::vector<Explosion> &_objects);

    void AddExplosion(const Point &point);


    void HandleMouseEvents(Event &event);

    void HandleKeyboardEvents(Event &event);

};

void from_json(const nlohmann::json &j, Level &value);