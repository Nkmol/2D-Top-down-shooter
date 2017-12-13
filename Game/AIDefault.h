#pragma once
#include "IAIBase.h"
#include "Helper.h"


class AIDefault :
	public HelperClasses::CloneableBase<IAIBase, AIDefault>
{
public:
	//http://www.stroustrup.com/C++11FAQ.html#inheriting
	using CloneableBase<IAIBase, AIDefault>::CloneableBase;

	void Update(int time) override;
	void Align() override;
	void NonNeighbourRelatedBehaviour() override;
	void NeighbourRelatedBehaviour(const GameObject *other) override;
	void Align(const GameObject *other) override;
	void Cohese(const GameObject* other) override;
	void Seperate(const GameObject* other) override;
	void GoTarget() override;
	~AIDefault();
protected:
	Point massCenter;
	int massSize;
};
