#include "WaveController.h"
#include "MoveableObject.h"
#include "Player.h"
#include "Wave.h"
#include "Config.h"


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
	return true;
}


void WaveController::SpawnWave()
{
	std::string waveText = "Wave: " + wavenumber;
	RenderManager::Instance().DrawText(waveText, 200, 100, 140, 20);
	std::cout << "new wave: " << wavenumber << endl;

	Point screenCenter;
	screenCenter.x = config::width / 2;
	screenCenter.y = config::height / 2;
	int minRadius = config::width / 2 * 1.1;
	int maxRadius = config::width / 2 * 1.5;

	for (auto flock : _curWave->GetFlocksVars())
	{
		for (int i = 0; i < flock.amount; i++) {
			int randomDistance = rand() % (maxRadius - minRadius + 1) + minRadius;
			int randomAngle = rand() % 360 + 1;
			auto member = make_unique<EnemyBase>(_j[flock.type], _npcs, _player);
			member->SetCoordinates(Point(randomDistance * cos(randomAngle) + screenCenter.x, randomDistance * sin(randomAngle) + screenCenter.y));

			_npcs->push_back(move(member));
		}
		
	}
	wavenumber++;
}