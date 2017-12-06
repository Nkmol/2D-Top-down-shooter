//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "FlockController.h"
#include "Flock.h"
#include "IAIBase.h"

using namespace std;

FlockController::FlockController()
{
}

FlockController::~FlockController()
{
}

void FlockController::GenerateFlock(const EnemyBase& basedOn, const int flockSize, const int minPos, const int maxPos, Player& flockTarget)
{
	auto leader = make_unique<EnemyBase>(basedOn);
	leader->SetCoordinates(Point(rand() % maxPos + minPos, rand() % maxPos + minPos));
	auto& ai = leader->GetBehaviour();
	ai.SetIsLeader(true);
	ai.SetTarget(flockTarget);

	auto newFlock = std::make_unique<Flock>(move(leader));
	for (auto i = 0; i < flockSize; i++)
	{
		auto member = make_unique<EnemyBase>(basedOn);
		member->SetCoordinates(Point(rand() % maxPos + minPos, rand() % maxPos + minPos));

		newFlock->AddMember(move(member));
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
