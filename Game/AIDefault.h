#pragma once
#include "IAIBase.h"
#include "Helper.h"


class AIDefault :
	public HelperClasses::CloneableBase<IAIBase, AIDefault>
{
public:
	//http://www.stroustrup.com/C++11FAQ.html#inheriting
	using CloneableBase<IAIBase, AIDefault>::CloneableBase;

	void Update(EnemiesType& others, int time) override;
	void Align() override;
	void Cohese(GameObject& other) override;
	void Seperate(GameObject& other) override;
	void GoTarget() override;
	~AIDefault();
};
