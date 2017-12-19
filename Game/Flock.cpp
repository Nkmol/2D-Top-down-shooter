//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "Flock.h"
#include "IAIBase.h"

Flock::Flock(EnemyRef leader) : _leader()
{
	_members.push_back(move(leader));
	_leader = _members.back();
}

void Flock::AddMember(const EnemyRef newMember)
{
	const auto shEnemy = newMember.lock();
	auto shLeader = _leader.lock();

	shEnemy->GetBehaviour().SetLeader(*shLeader.get());
	shEnemy->GetBehaviour().SetTarget(shLeader->GetBehaviour().GetTarget());
	_members.push_back(newMember);
}

void Flock::RemoveFarMembers()
{
	//todo alle members die ver weg zijn worden geremoved
}
//

void Flock::Update(const float time)
{
	auto member = _members.begin();
	while (member != _members.end())
	{
		if (const auto shMember = member->lock())
		{
			shMember->UpdatePosition(_members, time);
		}
		else
		{
			// Cleanup expired references
			member = _members.erase(member);
			continue;
		}

		++member;
	}
}

void Flock::Draw()
{
	for (auto const& member : _members)
	{
		if (const auto shMember = member.lock()) {
			shMember->draw();
		}
	}
}
