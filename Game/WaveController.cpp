#include "WaveController.h"

WaveController::WaveController()
{
	last_wave_timer = 0.0f;
}

void WaveController::Init(const int level, shared_ptr<Player> player, shared_ptr<std::vector<shared_ptr<MoveableObject>>> npcs)
{
	_level = level;
}

void WaveController::Update(float time)
{
	last_wave_timer += time;

	if (last_wave_timer >= 10.0f) {
		last_wave_timer = 0.0f;
		std::cout << "hoi" << endl;
		//flock_controller.GenerateFlock(20, 100, 900, _player, 50.0f);
	}
}

void WaveController::SpawnWave()
{

}