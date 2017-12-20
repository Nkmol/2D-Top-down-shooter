#pragma once
#include <iostream>
#include <memory>
#include <forward_list>
#include "RenderManager.h"
#include "json.hpp"
#include "EnemyBase.h"

class MoveableObject;
class Wave;
class Player;

class WaveController 
{
public:
	WaveController();
	void Init(std::forward_list<Wave> waves, std::shared_ptr<Player> player, std::vector<std::unique_ptr<EnemyBase>>* npcs);
	//returns false if there are no more waves
	bool Update(float time);
private:
	nlohmann::json _j;
	float _lastWaveTimer;
	void SpawnWave();
	std::forward_list<Wave> _waves;
	std::forward_list<Wave>::iterator _curWave;
	std::vector<std::unique_ptr<EnemyBase>>* _npcs;
	std::shared_ptr<Player> _player;
};