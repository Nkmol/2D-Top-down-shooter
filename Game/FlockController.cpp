//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "FlockController.h"
#include "Flock.h"
#include "IAIBase.h"
#include "MoveableObject.h"

using namespace std;

FlockController::FlockController()
{
}

FlockController::~FlockController() = default;

void FlockController::GenerateFlock(const EnemyBase& basedOn, const int flockSize, const int minPos, const int maxPos, Player& flockTarget, std::vector<std::shared_ptr<MoveableObject>>& gameObjects)
{
	auto leader = make_shared<EnemyBase>(basedOn);
	leader->SetCoordinates(Point(rand() % maxPos + minPos, rand() % maxPos + minPos));
	auto& ai = leader->GetBehaviour();
	ai.SetIsLeader(true);
	ai.SetTarget(flockTarget);

	gameObjects.push_back(move(leader));
	auto newFlock = std::make_unique<Flock>(weak_ptr<EnemyBase>(static_pointer_cast<EnemyBase>(gameObjects.back())));

	for (auto i = 0; i < flockSize; i++)
	{
		auto member = make_shared<EnemyBase>(basedOn);
		member->SetCoordinates(Point(rand() % maxPos + minPos, rand() % maxPos + minPos));

		gameObjects.push_back(move(member));
		newFlock->AddMember(weak_ptr<EnemyBase>(weak_ptr<EnemyBase>(static_pointer_cast<EnemyBase>(gameObjects.back()))));
	}

	_flocks.push_back(move(newFlock));
}

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
