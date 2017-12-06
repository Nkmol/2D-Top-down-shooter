#include "WaveController.h"
#include "MoveableObject.h"
#include "EnemyBase.h"

WaveController::WaveController()
{
	_lastWaveTimer = 0.0f;
}

void WaveController::Init(std::forward_list<Wave> waves, shared_ptr<Player> player)
{
	_waves = waves;
	_player = player;

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
	SpawnWave();
}

bool WaveController::Update(float time)
{
	_lastWaveTimer += time;

	if (_lastWaveTimer >= _curWave->get_time()) {
		_lastWaveTimer = 0.0f;
		_curWave++;
		if (_curWave == _waves.end())
			return false;
		SpawnWave();		
	}
	
	_flockController.UpdateFlocks(time);
	return true;
}

void WaveController::SpawnWave()
{
	std::string waveText = "Wave: " + _curWave->get_id();
	RenderManager::Instance().DrawText(waveText, 200, 100, 140, 20);
	std::cout << "new wave: " << _curWave->get_id() << endl;

	for (auto flock : _curWave->GetFlocksVars())
	{
		_flockController.GenerateFlock(_j[flock.type], flock.amount, flock.minPos, flock.maxPos, *_player);
	}
}

void WaveController::Draw()
{
	_flockController.DrawFlocks();
}