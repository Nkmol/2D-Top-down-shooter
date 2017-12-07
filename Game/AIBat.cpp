#include "AIBat.h"

void AIBat::Update(EnemiesType& others, int time)
{
	AIDefault::Update(others, time);
	if (_currentUpdateCounter % 50 == 0)
	{
		_weightMultiplier = rand() % 100 + 10;
	}
}

void AIBat::GoTarget()
{
	if (this->_currentUpdateCounter >= this->_maxUpdateCounter)
	{
		this->_currentUpdateCounter = 0;
		_attackTarget = !_attackTarget;
		this->_maxUpdateCounter = _attackTarget ? rand() % 75 + 50 : rand() % 60 + 30;
		if (!_attackTarget)
		{
			const auto rAngle = rand() % 360 + 1;
			const auto targetX = _owner->GetCoordinates().x + float(200 * cos(rAngle));
			const auto targetY = _owner->GetCoordinates().y + float(200 * sin(rAngle));
			_owner->SetDestinationPoint(Point(targetX, targetY));
		}
	}
	else
	{
		this->_currentUpdateCounter++;
	}

	if (_attackTarget)
	{
		AIDefault::GoTarget();
	}
}

std::unique_ptr<IAIBase> AIBat::Clone() const
{
	return make_unique<AIBat>(static_cast<AIBat const &>(*this));
}
