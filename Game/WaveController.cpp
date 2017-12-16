#include "WaveController.h"
#include "MoveableObject.h"
#include "EnemyBase.h"

WaveController::WaveController()
{
	_lastWaveTimer = 0.0f;
}

void WaveController::Init(std::forward_list<Wave> waves, shared_ptr<Player>& player, std::vector<std::shared_ptr<EnemyBase>>& npcs)
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

bool WaveController::Update(float time, std::vector<std::shared_ptr<EnemyBase>>& npcs, shared_ptr<Player>& player)
{
	_lastWaveTimer += time;

	if (_lastWaveTimer >= _curWave->GetTime()) {
		_lastWaveTimer = 0.0f;
		_curWave++;
		if (_curWave == _waves.end())
			return false;
		SpawnWave(npcs, player);
	}
	
	//_flockController.UpdateFlocks(time);
	return true;
}

void WaveController::SpawnWave(std::vector<std::shared_ptr<EnemyBase>>& npcs, shared_ptr<Player>& player)
{
	std::string waveText = "Wave: " + _curWave->GetId();
	RenderManager::Instance().DrawText(waveText, 200, 100, 140, 20);
	std::cout << "new wave: " << _curWave->GetId() << endl;

	for (auto flock : _curWave->GetFlocksVars())
	{
		//_flockController.GenerateFlock(_j[flock.type], flock.amount, flock.minPos, flock.maxPos, *player, npcs);
		for (auto i = 0; i < flock.amount; i++)
		{
			auto member = make_shared<EnemyBase>(_j[flock.type]);
			member->SetCoordinates(Point(rand() % flock.maxPos + flock.minPos, rand() % flock.maxPos + flock.minPos));

			npcs.push_back(move(member));
			//newFlock->AddMember(weak_ptr<EnemyBase>(weak_ptr<EnemyBase>(static_pointer_cast<EnemyBase>(gameObjects.back()))));
		}
	}
}

void WaveController::Draw()
{
	//_flockController.DrawFlocks();
}