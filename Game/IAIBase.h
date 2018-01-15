#pragma once
#include <vector>
#include <memory>
#include "Player.h"
#include "EnemyBase.h"

class IAIBase
{
protected:
	using EnemiesType = std::vector<weak_ptr<EnemyBase>>;
	int _weightMultiplier;


	// Todo Smart pointer for non-owning pointer? (actually a nullable-reference) -> probably weak_ptr?
	const Point* _target;
	const EnemyBase* _leader;
	EnemyBase* _owner;

	bool _isLeader;

	const int COLLIDABLEWEIGHTMULTIPLIER = 7500;
public:
	IAIBase(EnemyBase& owner, const unsigned weightMultiplier, const bool isLeader, const Point& target) : _weightMultiplier(weightMultiplier), _target(&target), _owner(&owner), _isLeader(isLeader)
	{
	}

	IAIBase(EnemyBase& owner) : IAIBase(owner, 100, false, {})
	{
	}

	IAIBase()
	{
	}

	void SetOwner(EnemyBase& owner)
	{
		_owner = &owner;
	}

	void SetIsLeader(const bool value)
	{
		_isLeader = value;
	}

	void SetTarget(const Point& target)
	{
		_target = &target;
	}

	void SetLeader(const EnemyBase& leader)
	{
		_leader = &leader;
	}

	const EnemyBase& GetLeader() const
	{
		return *_leader;
	}

	const Point& GetTarget() const
	{
		return *_target;
	}

	bool IsLeader() const
	{
		return _isLeader;
	}

	void SetWeightMultiplier(const int value)
	{
		_weightMultiplier = value;
	}

	virtual ~IAIBase() {}
	virtual void Update(float time) = 0;
	virtual Point Align() = 0;
	virtual Point Cohese() = 0;
	virtual Point Seperate() = 0;
	//virtual Point CohesePlayer() = 0;
	virtual void GoTarget() = 0;
	virtual unique_ptr<IAIBase> Clone() const = 0;
};
