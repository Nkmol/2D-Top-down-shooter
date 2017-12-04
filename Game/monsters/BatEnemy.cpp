//
// Created by Ahmad Rahimi on 11/29/17.
//

#include "BatEnemy.h"

namespace Properties
{
	const float AttrSpeed = 260.0f;
	const int AttrDmg = 5;
	const int AttrLp = 15;
	const int AttrReward = 5;
	const int WeightMultiplier = 10;
}

BatEnemy::BatEnemy(const Point& coordinates, const bool isLeader) : EnemyBase(
	"bat", coordinates, Properties::AttrSpeed, isLeader, Properties::AttrDmg,
	Properties::AttrLp, Properties::AttrReward)
{
	this->weightMultiplier = Properties::WeightMultiplier;
}

void BatEnemy::update(const float time)
{
	EnemyBase::update(time);
	if (this->_currentUpdateCounter % 50 == 0)
	{
		this->weightMultiplier = rand() % 100 + 10;
	}
}

void BatEnemy::GoTarget()
{
	if (this->_currentUpdateCounter >= this->_maxUpdateCounter)
	{
		this->_currentUpdateCounter = 0;
		_attackTarget = !_attackTarget;
		this->_maxUpdateCounter = _attackTarget ? rand() % 75 + 50 : rand() % 60 + 30;
		if (!_attackTarget)
		{
			const auto rAngle = rand() % 360 + 1;
			const auto targetX = this->GetCoordinates().x + float(200 * cos(rAngle));
			const auto targetY = this->GetCoordinates().y + float(200 * sin(rAngle));
			this->destinationPoint = Point(targetX, targetY);
		}
	}
	else
	{
		this->_currentUpdateCounter++;
	}

	if (_attackTarget)
	{
		EnemyBase::GoTarget();
	}
}
