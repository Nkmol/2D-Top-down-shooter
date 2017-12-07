//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "FlockController.h"
#include "../monsters/ZombieEnemy.h"
#include "../monsters/BatEnemy.h"

using namespace std;

template <class T>
void FlockController::GenerateFlock(const int flockSize, const int minPos, const int maxPos, Player& flockTarget, std::vector<shared_ptr<GameObject>> &gameObjects)
{
	auto leader = make_unique<T>(Point(rand() % maxPos + minPos, rand() % maxPos + minPos), true);
	leader->setTarget(flockTarget);

	auto newFlock = std::make_unique<Flock>(move(leader));
	for (auto i = 0; i < flockSize; i++)
	{
		auto member = make_shared<T>(Point(rand() % maxPos + minPos, rand() % maxPos + minPos), false);
		newFlock->AddMember(member);
		gameObjects.push_back(member);
	}

	_flocks.push_back(move(newFlock));
}

template void FlockController::GenerateFlock<ZombieEnemy>(const int flockSize, const int minPos, const int maxPos,
	Player& flockTarget, std::vector<shared_ptr<GameObject>> &gameObjects);
template void FlockController::GenerateFlock<BatEnemy>(const int flockSize, const int minPos, const int maxPos,
	Player& flockTarget, std::vector<shared_ptr<GameObject>> &gameObjects);

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