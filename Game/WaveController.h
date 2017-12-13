#pragma once
#include <iostream>
#include <forward_list>
#include <GameObject.h>
#include "RenderManager.h"
#include "FlockController.h"
#include "json.hpp"
#include "Wave.h"

class MoveableObject;
class Wave;
class WaveController 
{
public:
	WaveController();
	void Init(std::forward_list<Wave> waves, shared_ptr<Player> player, std::vector<std::shared_ptr<GameObject>>& _npcs);
	//returns false if there are no more waves
	bool Update(float time, std::vector<std::shared_ptr<GameObject>>& _npcs);
	void Draw();
private:
	nlohmann::json _j;
	float _lastWaveTimer;
	void SpawnWave(std::vector<std::shared_ptr<GameObject>>& npcs);
	FlockController _flockController;
	shared_ptr<Player> _player;
	std::forward_list<Wave> _waves;
	std::forward_list<Wave>::iterator _curWave;
	std::vector<std::shared_ptr<GameObject>> _npcs;
};