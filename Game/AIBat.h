#pragma once
#include "AIDefault.h"

class AIBat : public AIDefault

{
	int _currentUpdateCounter = 0, _maxUpdateCounter = 50;
	bool _attackTarget = true;
public:
	using AIDefault::AIDefault;

	void Update(int time) override;
	void GoTarget() override;
	void NeighbourRelatedBehaviour(const GameObject *other) override;
	void NonNeighbourRelatedBehaviour() override;
	// TODO Make sure CRTP can use multiple levels of inheritance
	// This is a quick for this, but HelperClasses::CloneableBase should be resposible for this
	std::unique_ptr<IAIBase> Clone() const override;
};

