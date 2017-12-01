//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_FLOCK_H
#define SHOOTER_FLOCK_H


#include "EnemyBase.h"
#include "memory"
#include "vector"

class Flock
{
	EnemyBase& _leader;
	vector<unique_ptr<EnemyBase>> _members;
	std::map<string, std::vector<EnemyBase>> quadtree;
public:
	explicit Flock(unique_ptr<EnemyBase> leader);
	void AddMember(unique_ptr<EnemyBase> newMember);
	void RemoveFarMembers();
	void Update(float time);
	string placeEnemyAtQuadrant(EnemyBase& replaceEnemy);
	void Draw();

	int mapH;
    int mapW;
};


#endif //SHOOTER_FLOCK_H
