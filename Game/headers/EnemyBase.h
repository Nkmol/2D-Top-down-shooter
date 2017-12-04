//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_ENEMYBASE_H
#define SHOOTER_ENEMYBASE_H


#include <Point.h>
#include <vector>
#include "memory"
#include "Player.h"
#include "../IAIBase.h"

class EnemyBase : public MoveableObject  {

protected:
	using EnemiesType = vector<unique_ptr<EnemyBase>>;
	unique_ptr<IAIBase> _behaviour;

	int lifepoints, damage, reward;
	Point destinationPoint;

	const int getLifepoints() const;
	const int changeLifepoints(const int lp);
	const int getDamage() const;
	const int getReward() const;
public:
    EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward = 50);
	EnemyBase(const std::string& filePath, Point coordinates, float speed, bool isLeader, int damage, int lifepoints,
	          int reward);
	EnemyBase(const json & j);

	void UpdatePosition(EnemiesType& others, const float time);

    void ApplyForce(float forcePower, int forceDirection);

    //getters
	const Point& GetDestinationPoint() const;
	IAIBase& GetBehaviour() const;

    //setters
	void SetDestination(const Point& point);
	void SetDestinationPoint(const Point& point);

	void update(const float time);
    void draw();
};


#endif //SHOOTER_ENEMYBASE_H
