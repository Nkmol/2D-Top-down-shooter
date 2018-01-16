#pragma once
#include <iostream>
#include <memory>
#include <forward_list>
#include "RenderManager.h"
#include "json.hpp"
#include "EnemyBase.h"
#include "../Engine/UIText.h"

class MoveableObject;
class Wave;
class Player;

class WaveController 
{
public:
	WaveController();
	~WaveController();
	void Init(std::forward_list<Wave> waves, std::shared_ptr<Player> player, std::vector<std::unique_ptr<EnemyBase>>* npcs);
	//returns false if there are no more waves
	bool Update(float time, int levelnumber);
private:
	nlohmann::json _j;
	float _lastWaveTimer, _multiplier = 1.0;
	int _waveNumber = 1;
	void SpawnWave();
	std::forward_list<Wave> _waves;
	std::forward_list<Wave>::iterator _curWave;
	std::vector<std::unique_ptr<EnemyBase>>* _npcs;
	std::shared_ptr<Player> _player;
};