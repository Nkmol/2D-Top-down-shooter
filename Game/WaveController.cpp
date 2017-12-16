#include "WaveController.h"
#include "MoveableObject.h"
#include "Player.h"
#include "Wave.h"


WaveController::WaveController()
{
	_lastWaveTimer = 0.0f;
}

void WaveController::Init(std::forward_list<Wave> waves, std::shared_ptr<Player> player, std::vector<std::unique_ptr<EnemyBase>>* npcs)
{
	_waves = waves;
	_npcs = npcs;
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

	if (_lastWaveTimer >= _curWave->GetTime()) {
		_lastWaveTimer = 0.0f;
		_curWave++;
		if (_curWave == _waves.end())
			return false;
		SpawnWave();
	}
	return true;
}

void WaveController::SpawnWave()
{
	std::string waveText = "Wave: " + _curWave->GetId();
	RenderManager::Instance().DrawText(waveText, 200, 100, 140, 20);
	std::cout << "new wave: " << _curWave->GetId() << endl;

	for (auto flock : _curWave->GetFlocksVars())
	{
		for (int i = 0; i < flock.amount; i++) {
			auto member = make_unique<EnemyBase>(_j[flock.type], _npcs, _player);
			member->SetCoordinates(Point(rand() % flock.maxPos + flock.minPos, rand() % flock.maxPos + flock.minPos));

			_npcs->push_back(move(member));
		}
		
	}
}
