#pragma once
#include "IAIBase.h"

class AIDefault :
	public IAIBase
{
	//http://www.stroustrup.com/C++11FAQ.html#inheriting
	using IAIBase::IAIBase;
public:
	void Update(EnemiesType& others, int time) override;
	void Align() override;
	void Cohese(EnemiesType& others) override;
	void Seperate(EnemiesType& others) override;
	void GoTarget() override;
	~AIDefault();
};

