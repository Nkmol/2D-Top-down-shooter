#pragma once
#include "IAIBase.h"
#include "Helper.h"


class AIDefault :
	public HelperClasses::CloneableBase<IAIBase, AIDefault>
{
	float _maxSpeed = 2.0;
	float _maxForce = 0.1;
	Point acceleration_;
	Point _velocity;
public:
	//http://www.stroustrup.com/C++11FAQ.html#inheriting
	using CloneableBase<IAIBase, AIDefault>::CloneableBase;

	void Update(float time) override;
	void ApplyForce(const Point& force);
	Point Align() override;
	Point Cohese() override;
	Point seek(const Point& target) const;
	Point Seperate() override;
	//void CohesePlayer() override;
	void GoTarget() override;
	~AIDefault();
};
