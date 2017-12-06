#pragma once

#include <vector>
#include <memory>
#include "FlockController.h"
#include <SDL.h>

class Player;
class MoveableObject;
class GameObject;

class Level {
    int _level;
    std::vector<std::shared_ptr<MoveableObject>> _objs;
	std::vector<std::shared_ptr<MoveableObject>> _objsNoEnemies;
    std::vector<std::shared_ptr<MoveableObject>> _npcs;
    std::vector<std::shared_ptr<GameObject>> _loot;
	std::shared_ptr<Player> _player;

private:
    FlockController _flockController;
	double _levelSpeed;
    int counter = 0;
    int totalms = 0;

public:
    explicit Level(int level);

    void Init();

    void HandleEvents(SDL_Event event);

    void Update(float time);

    void Draw();
};