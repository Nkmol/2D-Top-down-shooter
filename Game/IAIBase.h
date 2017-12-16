#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "EnemyBase.h"

class IAIBase
{
protected:
	using EnemiesType = std::vector<std::shared_ptr<EnemyBase>>;
	int _weightMultiplier;


	// Todo Smart pointer for non-owning pointer? (actually a nullable-reference) -> probably weak_ptr?
	const Player* _target;
	//const EnemyBase* _leader;
	EnemyBase* _owner;

	//bool _isLeader;

	const int COLLIDABLEWEIGHTMULTIPLIER = 10000;
public:
	IAIBase(EnemyBase& owner, const unsigned weightMultiplier, const bool isLeader) : _owner(&owner), _weightMultiplier(weightMultiplier)
	{
	}

	IAIBase(EnemyBase& owner) : IAIBase(owner, 100, false)
	{
	}

	IAIBase()
	{
	}

	void SetOwner(EnemyBase& owner)
	{
		_owner = &owner;
	}

	void SetTarget(const Player& target)
	{
		_target = &target;
	}

	const Player& GetTarget() const
	{
		return *_target;
	}

	void SetWeightMultiplier(const int value)
	{
		_weightMultiplier = value;
	}

	virtual ~IAIBase() {}
	virtual void Update(EnemiesType& others, int time) = 0;
	virtual void Align(EnemiesType& others) = 0;
	virtual void Cohese(EnemiesType& others) = 0;
	virtual void Seperate(EnemiesType& others) = 0;
	virtual void GoTarget() = 0;
	virtual unique_ptr<IAIBase> Clone() const = 0;
};
