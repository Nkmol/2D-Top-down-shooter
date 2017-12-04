//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "FlockController.h"
#include "../monsters/ZombieEnemy.h"
#include "../monsters/BatEnemy.h"

using namespace std;

// TODO way to type-hint T
template <class T>
void FlockController::GenerateFlock(const int flockSize, const int minPos, const int maxPos, Player& flockTarget)
{
	auto leader = make_unique<T>(Point(rand() % maxPos + minPos, rand() % maxPos + minPos), true);
	leader->GetBehaviour().SetTarget(flockTarget);

	auto newFlock = std::make_unique<Flock>(move(leader));
	for (auto i = 0; i < flockSize; i++)
	{
		auto member = make_unique<T>(Point(rand() % maxPos + minPos, rand() % maxPos + minPos), false);
		newFlock->AddMember(move(member));
	}

	_flocks.push_back(move(newFlock));
}

// TODO just use EnemyBase -> need to move to header probably
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
