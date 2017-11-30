//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_ENEMYBASE_H
#define SHOOTER_ENEMYBASE_H


#include <Point.h>
#include <vector>
#include "memory"
#include "Player.h"
#include "Helper.h"
class EnemyBase : public MoveableObject  {
    bool isLeader;
	const EnemyBase* leader; // Todo Smart pointer for non-owning pointer? (actually a nullable-reference) -> probably weak_ptr?

protected:
	int lifepoints, damage, reward, weightMultiplier = 100;
	Point destinationPoint;
	const Player* target; // Todo Smart pointer for non-owning pointer? (actually a nullable-reference) -> probably weak_ptr?
	const int getLifepoints() const;
	const int changeLifepoints(const int lp);
	const int getDamage() const;
	const int getReward() const;

public:
    EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward = 50);
	EnemyBase(const std::string& filePath, Point coordinates, float speed, bool isLeader, int damage, int lifepoints,
	          int reward);
	void updatePositions(std::vector<unique_ptr<EnemyBase>>& others, float time);

    //algorithms
    void align();
    void cohese(std::vector<shared_ptr<EnemyBase>>& others);
    void seperate(std::vector<shared_ptr<EnemyBase>>& others);
    void applyForce(float forcePower, int forceDirection);

	virtual void goTarget();

    //getters
	const Player& getTarget() const;

    //setters
    void setTarget(const Player& target);
    void setLeader(const EnemyBase& leader);

    void update(float time);
    void draw();
};


#endif //SHOOTER_ENEMYBASE_H
