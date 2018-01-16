#pragma once
#include "IAIBase.h"
#include "Helper.h"


class AIDefault :
	public HelperClasses::CloneableBase<IAIBase, AIDefault>
{
public:
	//http://www.stroustrup.com/C++11FAQ.html#inheriting
	using CloneableBase<IAIBase, AIDefault>::CloneableBase;
	void Update(float time) override;
	void Align() override;
	void Cohese() override;
	void Seperate() override;
	void CohesePlayer() override;
	void GoTarget() override;
	~AIDefault();
};
