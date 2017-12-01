//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "Flock.h"

Flock::Flock(EnemyBase&& leader) : _leader(leader)
{
	_members.push_back(make_unique<EnemyBase>(leader));
}

void Flock::AddMember(EnemyBase&& newMember)
{
	newMember.setLeader(_leader);
	newMember.setTarget(_leader.getTarget());
	_members.push_back(make_unique<EnemyBase>(move(newMember)));
}

void Flock::RemoveFarMembers()
{
	//todo alle members die ver weg zijn worden geremoved
}

void Flock::Update(const float time)
{
	//todo een manier vinden om alleen objecten mee te sturen die in de buurt zijn
	for (auto const& member : _members)
	{
		member->UpdatePositions(_members, time);
	}
}

void Flock::Draw()
{
	for (auto const& member : _members)
	{
		member->draw();
	}
}
