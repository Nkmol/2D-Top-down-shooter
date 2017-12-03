//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_ENEMYBASE_H
#define SHOOTER_ENEMYBASE_H


#include <Point.h>
#include <vector>
#include "memory"
#include "Player.h"
#include "MoveableObject.h"
#include "Helper.h"

class EnemyBase : public MoveableObject  {

protected:
	using EnemiesType = vector<shared_ptr<EnemyBase>>;
	int lifepoints, damage, reward, weightMultiplier = 100;
	Point destinationPoint;

	// Todo Smart pointer for non-owning pointer? (actually a nullable-reference) -> probably weak_ptr?
	const Player* _target;
	const EnemyBase* _leader;

	bool isLeader;
	const int getLifepoints() const;
	const int changeLifepoints(const int lp);
	const int getDamage() const;
	const int getReward() const;
public:
    EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward = 50);
	EnemyBase(const std::string& filePath, Point coordinates, float speed, bool isLeader, int damage, int lifepoints,
	          int reward);

	void UpdatePositions(EnemiesType& others, float time);

    //algorithms
    void Align();
    void Cohese(EnemiesType& others);
    void Seperate(EnemiesType& others);
    void ApplyForce(float forcePower, int forceDirection);

	virtual void GoTarget();

    //getters
	const Player& getTarget() const;

    //setters
    void setTarget(const Player& target);
    void setLeader(const EnemyBase& leader);

    void update(float time);
    void draw();
};


#endif //SHOOTER_ENEMYBASE_H
