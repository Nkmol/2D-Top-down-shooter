#include "WaveController.h"
#include "MoveableObject.h"
#include "EnemyBase.h"

WaveController::WaveController()
{
	_lastWaveTimer = 0.0f;
}

void WaveController::Init(std::forward_list<Wave> waves, shared_ptr<Player>& player, std::vector<std::shared_ptr<MoveableObject>>& npcs)
{
	_waves = waves;

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
	SpawnWave(npcs, player);
}

bool WaveController::Update(float time, std::vector<std::shared_ptr<MoveableObject>>& npcs, shared_ptr<Player>& player, int levelnumber)
{
	_lastWaveTimer += time * multiplier;

	if (_lastWaveTimer >= _curWave->GetTime()) {
		_lastWaveTimer = 0.0f;
		_curWave++;
		if (_curWave == _waves.end() & levelnumber != 3){
			return false;
		}
		else if (_curWave == _waves.end() & levelnumber == 3){
			_curWave = _waves.begin();
			multiplier = multiplier * 1.2;
		}
		SpawnWave(npcs, player);
	}
	
	_flockController.UpdateFlocks(time);
	return true;
}

void WaveController::SpawnWave(std::vector<std::shared_ptr<MoveableObject>>& npcs, shared_ptr<Player>& player)
{
	std::string waveText = "Wave: " + wavenumber;
	RenderManager::Instance().DrawText(waveText, 200, 100, 140, 20);
	std::cout << "new wave: " << wavenumber << endl;

	for (auto flock : _curWave->GetFlocksVars())
	{
		_flockController.GenerateFlock(_j[flock.type], flock.amount * multiplier, flock.minPos, flock.maxPos, *player, npcs);
	}
	wavenumber++;
}

void WaveController::Draw()
{
	_flockController.DrawFlocks();
}