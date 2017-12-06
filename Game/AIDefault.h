#pragma once
#include "IAIBase.h"

// https://katyscode.wordpress.com/2013/08/22/c-polymorphic-cloning-and-the-crtp-curiously-recurring-template-pattern/
//http://www.stroustrup.com/C++11FAQ.html#inheriting

// CRTP idiom - https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
template <class Base, class Derived>
class CloneableBase : public Base
{
public:
	using Base::Base;
	virtual unique_ptr<Base> Clone() const
	{
		return make_unique<Derived>(static_cast<Derived const &>(*this)); // call the copy ctor.
	}
protected:
	~CloneableBase() {};
	friend Derived;
};


class AIDefault :
	public CloneableBase<IAIBase, AIDefault>
{
	using CloneableBase<IAIBase, AIDefault>::CloneableBase;
public:
	void Update(EnemiesType& others, int time) override;
	void Align() override;
	void Cohese(EnemiesType& others) override;
	void Seperate(EnemiesType& others) override;
	void GoTarget() override;
	~AIDefault();
};
