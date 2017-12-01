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
#include <time.h>
class EnemyBase : public MoveableObject, public std::enable_shared_from_this<EnemyBase>  {
    bool isLeader;
    shared_ptr<EnemyBase> leader;

protected:
	int lifepoints, damage, reward, weightMultiplier = 100;
	Point destinationPoint;
	shared_ptr<Player> target;
	const int getLifepoints() const;
	const int changeLifepoints(const int lp);
	const int getDamage() const;
	const int getReward() const;
	static std::atomic<int> s_id;

public:
    EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward = 50);
	EnemyBase(const std::string& filePath, Point coordinates, float speed, bool isLeader, int damage, int lifepoints,
	          int reward);
	void updatePositions(std::vector<EnemyBase> &others, float time);

	string currentQuadrant = "1111";
	int currentQuadrantIndex = -1;
	int id = 0;

    //algorithms
    void align();
    void cohese(std::vector<EnemyBase> &others);
    void seperate(std::vector<EnemyBase> &others);
    void applyForce(float forcePower, int forceDirection);
    string getCurrentQuadrant() const;

	virtual void goTarget();

    //getters
    const shared_ptr<Player> &getTarget() const;

    //setters
    void setTarget(const shared_ptr<Player> &target);
    void setLeader(const shared_ptr<EnemyBase> &leader);

    void update(float time);
    void draw();

	//comparers
	friend bool operator==(EnemyBase& enemyBase1, const EnemyBase& enemyBase2);
};


#endif //SHOOTER_ENEMYBASE_H
