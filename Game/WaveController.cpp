#include "WaveController.h"

WaveController::WaveController()
{
	_lastWaveTimer = 0.0f;
}

void WaveController::Init(std::forward_list<Wave> waves, shared_ptr<Player> player, shared_ptr<std::vector<shared_ptr<MoveableObject>>> npcs)
{
	_waves = waves;
	_player = player;
	_npcs = npcs;
	_curWave = _waves.begin();
	SpawnWave();
}

void WaveController::Update(float time)
{
	_lastWaveTimer += time;

	if (_lastWaveTimer >= _curWave->get_time()) {
		_lastWaveTimer = 0.0f;
		_curWave++;
		SpawnWave();		
	}


	_flockController.UpdateFlocks(time);
}

void WaveController::SpawnWave()
{
	std::string waveText = "Wave: " + _curWave->get_id();
	RenderManager::Instance().DrawText(waveText, 200, 100, 140, 20);
	std::cout << "new wave: " << _curWave->get_id() << endl;
	
	_flockController.GenerateFlock<ZombieEnemy>(20, 200, 600, *_player);
	//_flockController.GenerateFlock<BatEnemy>(50, 200, 600, *_player);
}

void WaveController::Draw()
{
	_flockController.DrawFlocks();
}