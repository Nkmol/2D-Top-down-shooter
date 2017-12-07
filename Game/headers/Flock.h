//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_FLOCK_H
#define SHOOTER_FLOCK_H

#include <memory>
#include <vector>

class EnemyBase;

class Flock
{
public:
	//using EnemiesType = std::vector<unique_ptr<EnemyBase>>; 
private:
	EnemyBase& _leader;
	std::vector<std::shared_ptr<EnemyBase>> _members;
public:
	explicit Flock(std::unique_ptr<EnemyBase> leader);
	void AddMember(std::shared_ptr<EnemyBase> newMember);
	void RemoveFarMembers();
	void Update(float time);
	void Draw();
};


#endif //SHOOTER_FLOCK_H
