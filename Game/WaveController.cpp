#include "WaveController.h"
#include "MoveableObject.h"
#include "EnemyBase.h"

WaveController::WaveController()
{
	_lastWaveTimer = 0.0f;
}

void WaveController::Init(std::forward_list<Wave> waves, shared_ptr<Player> player, std::vector<std::shared_ptr<MoveableObject>>& npcs)
{
	_waves = waves;
	_player = player;
	_npcs = npcs;

	std::ifstream i;
	i.exceptions(ifstream::failbit | ifstream::badbit);
	try
	{
		i.open("../content/config/monsters.meta.json");
	}
	catch (const ifstream::failure&)
	{
		cout << "Exception opening/reading file" << endl;
		return;
	}
	
	i >> _j;

	_curWave = _waves.begin();
	//SpawnWave(npcs);
}

bool WaveController::Update(float time, std::vector<std::shared_ptr<MoveableObject>>& npcs)
{
	_lastWaveTimer += time;

	if (_lastWaveTimer >= _curWave->GetTime()) {
		_lastWaveTimer = 0.0f;
		_curWave++;
		if (_curWave == _waves.end())
			return false;
		//SpawnWave(npcs);		
	}
	
	_flockController.UpdateFlocks(time);
	return true;
}

void WaveController::SpawnWave(std::vector<std::shared_ptr<MoveableObject>>& npcs)
{
	std::string waveText = "Wave: " + _curWave->GetId();
	RenderManager::Instance().DrawText(waveText, 200, 100, 140, 20);
	std::cout << "new wave: " << _curWave->GetId() << endl;

	for (auto flock : _curWave->GetFlocksVars())
	{
		_flockController.GenerateFlock(_j[flock.type], flock.amount, flock.minPos, flock.maxPos, *_player, npcs);
	}
}

void WaveController::Draw()
{
	_flockController.DrawFlocks();
}