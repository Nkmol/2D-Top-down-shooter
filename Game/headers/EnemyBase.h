//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_ENEMYBASE_H
#define SHOOTER_ENEMYBASE_H

#include <memory>
#include "Point.h"
#include "MoveableObject.h"
#include <json.hpp>

class IAIBase;

class EnemyBase : public MoveableObject {

protected:
	// TODO share same AI parts (shared_ptr)
	std::unique_ptr<IAIBase> _behaviour;

	int lifepoints, damage, reward;
	Point destinationPoint;

	const int getLifepoints() const;
	const int changeLifepoints(const int lp);
	const int getDamage() const;
	const int getReward() const;
public:
	EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward = 50);
	EnemyBase(const std::string& filePath, const Point& coordinates, const float speed, const bool isLeader,
		const int damage, const int lifepoints, const int reward);
	EnemyBase(const nlohmann::json & j);
	EnemyBase(const EnemyBase& other);
	virtual ~EnemyBase();

	void UpdatePosition(std::vector<shared_ptr<EnemyBase>>& others, const float time);

	void ApplyForce(float forcePower, int forceDirection);

	//getters
	const Point& GetDestinationPoint() const;
	IAIBase& GetBehaviour() const;
	Point GetPointToTarget();

	//setters
	void SetDestination(const Point& point);
	void SetDestinationPoint(const Point& point);

	void update(const float time);
	void draw();
};


#endif //SHOOTER_ENEMYBASE_H