//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "FlockController.h"
#include "../monsters/ZombieEnemy.h"
#include "../monsters/BatEnemy.h"

using namespace std;

template <class T>
void FlockController::GenerateFlock(const int flockSize, const int minPos, const int maxPos, Player& flockTarget)
{
	T leader(Point(rand() % maxPos + minPos, rand() % maxPos + minPos), true);
	leader.setTarget(flockTarget);

	auto newFlock = std::make_unique<Flock>(move(leader));
	for (auto i = 0; i < flockSize; i++)
	{
		newFlock->AddMember(T{Point(rand() % maxPos + minPos, rand() % maxPos + minPos), false});
	}

	_flocks.push_back(move(newFlock));
}

template void FlockController::GenerateFlock<ZombieEnemy>(const int flockSize, const int minPos, const int maxPos,
                                                          Player& flockTarget);
template void FlockController::GenerateFlock<BatEnemy>(const int flockSize, const int minPos, const int maxPos,
                                                       Player& flockTarget);

void FlockController::DrawFlocks()
{
	for (auto const& flock : _flocks)
	{
		flock->Draw();
	}
}

void FlockController::UpdateFlocks(const float time)
{
	for (auto const& flock : _flocks)
	{
		flock->Update(time);
	}
}
