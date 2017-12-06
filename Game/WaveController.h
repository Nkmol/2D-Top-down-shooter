#pragma once
#include <iostream>
#include <forward_list>
#include "RenderManager.h"
#include "FlockController.h"
#include "Wave.h"
#include "monsters\ZombieEnemy.h"

class WaveController 
{
public:
	WaveController();
	void Init(std::forward_list<Wave> waves, shared_ptr<Player> player, shared_ptr<std::vector<shared_ptr<MoveableObject>>> npcs);
	void Update(float time);
	void Draw();
private:
	float _lastWaveTimer;
	void SpawnWave();
	FlockController _flockController;
	shared_ptr<Player> _player;
	shared_ptr<std::vector<shared_ptr<MoveableObject>>> _npcs;
	std::forward_list<Wave> _waves;
	std::forward_list<Wave>::iterator _curWave;
};