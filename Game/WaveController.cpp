#include "WaveController.h"
#include "MoveableObject.h"
#include "Player.h"
#include "Wave.h"
#include "Config.h"
#include "Hud.h"
#include "../Engine/UIText.h"


WaveController::WaveController()
{
	_lastWaveTimer = 0.0f;
}

WaveController::~WaveController()
{
	Hud::Instance().Get<UIText>("Counter")->Destroy();
}

void WaveController::Init(std::forward_list<Wave> waves, std::shared_ptr<Player> player, std::vector<std::unique_ptr<EnemyBase>>* npcs)
{
	_waves = waves;
	_npcs = npcs;
	_player = player;

	Hud::Instance().AddComponent("Counter", std::make_unique<UIText>(UIText("", 20, { config::width / 2 - 50, 5 })));

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

bool WaveController::Update(float time, int levelnumber)
{
	if (_npcs->empty()) {
		_curWave++;
		if (_curWave == _waves.end() & levelnumber != 3)
		{
			return false;
		}
		else if (_curWave == _waves.end() & levelnumber == 3)
		{
			_curWave = _waves.begin();
			_multiplier *= 1.2;
		}
		SpawnWave();
	}
	return true;
}


void WaveController::SpawnWave()
{
	std::cout << "new wave: " << _curWave->GetId() << endl;
	std::string waveText = "Wave " + std::to_string(_waveNumber) + " incoming!";
	Hud::Instance().AddComponent("Incoming", make_unique<UIText>(UIText(waveText, 40, Point(config::width / 2 - 180, 100), 2.0f)));
	Hud::Instance().Get<UIText>("Counter")->ChangeText("Wave: " + std::to_string(_waveNumber));

	Point screenCenter;
	screenCenter.x = config::width / 2;
	screenCenter.y = config::height / 2;
	int minRadius = config::width / 2 * 1.1;
	int maxRadius = config::width / 2 * 2.7;

	for (auto flock : _curWave->GetFlocksVars())
	{
		for (int i = 0; i < flock.amount*_multiplier; i++) {
			int randomDistance = rand() % (maxRadius - minRadius + 1) + minRadius;
			int randomAngle = rand() % 360 + 1;
			auto member = make_unique<EnemyBase>(_j[flock.type], _npcs, _player);
			member->SetCoordinates(Point(randomDistance * cos(randomAngle) + screenCenter.x, randomDistance * sin(randomAngle) + screenCenter.y));

			_npcs->push_back(move(member));
		}		
	}
	_waveNumber++;
}