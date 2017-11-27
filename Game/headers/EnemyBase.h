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
class EnemyBase : public MoveableObject, public std::enable_shared_from_this<EnemyBase>  {
    Point destinationPoint;
    bool isLeader;
    shared_ptr<EnemyBase> leader;
    shared_ptr<Player> target;

protected:
	int lifepoints;
	int damage;
	int reward;
	
	const int getLifepoints() const;
	const int changeLifepoints(const int lp);
	const int getDamage() const;
	const int getReward() const;

public:
    EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward = 50);
	EnemyBase(const std::string& filePath, Point coordinates, float speed, bool isLeader, int damage, int lifepoints,
	          int reward);
	void updatePositions(std::vector<shared_ptr<EnemyBase>> others, float time);

    //algorithms
    void align();
    void cohese(std::vector<shared_ptr<EnemyBase>> others);
    void seperate(std::vector<shared_ptr<EnemyBase>> others);
    void applyForce(float forcePower, int forceDirection);
    void goTarget();

    //getters
    const shared_ptr<Player> &getTarget() const;

    //setters
    void setTarget(const shared_ptr<Player> &target);
    void setLeader(const shared_ptr<EnemyBase> &leader);

    void update(float time);
    void draw();
};


#endif //SHOOTER_ENEMYBASE_H
