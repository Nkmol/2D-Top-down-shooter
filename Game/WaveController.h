#pragma once
#include <iostream>
#include "FlockController.h"

class WaveController 
{
public:
	WaveController();
	void Init(const int level, shared_ptr<Player> player, shared_ptr<std::vector<shared_ptr<MoveableObject>>> npcs);
	void Update(float time);
private:
	int _level;
	float last_wave_timer;
	FlockController flock_controller;
	void SpawnWave();
	shared_ptr<Player> _player;
	shared_ptr<std::vector<shared_ptr<MoveableObject>>> _npcs;
};