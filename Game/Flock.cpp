//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "Flock.h"
#include "IAIBase.h"

Flock::Flock(unique_ptr<EnemyBase> leader) : _leader(*leader)
{
	_members.push_back(move(leader));
}

void Flock::AddMember(unique_ptr<EnemyBase> newMember)
{
	newMember->GetBehaviour().SetLeader(_leader);
	newMember->GetBehaviour().SetTarget(_leader.GetBehaviour().GetTarget());
	_members.push_back(move(newMember));
}

void Flock::RemoveFarMembers()
{
	//todo alle members die ver weg zijn worden geremoved
}
//

void Flock::Update(const float time)
{
	//todo een manier vinden om alleen objecten mee te sturen die in de buurt zijn
  //_leader.UpdatePosition(_members, time);
  for (auto const &member: this->_members) {
      member->UpdatePosition(_members, time);
  }
}

void Flock::Draw()
{
	for (auto const& member : _members)
	{
		member->draw();
	}
}
