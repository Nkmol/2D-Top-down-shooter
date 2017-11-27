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

class Level
{
	int _level;
	std::vector<shared_ptr<MoveableObject>> _objs;
	std::vector<shared_ptr<MoveableObject>> _npcs;
	std::vector<shared_ptr<GameObject>> _loot;
	shared_ptr<Player> _player;
	FlockController _flockController;
	
public:
	Level(int level);
	void Init();
	void HandleEvents(SDL_Event event);
	void Update(float time);
	void Draw();
};