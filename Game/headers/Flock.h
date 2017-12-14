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
private:
	using EnemyRef = std::weak_ptr<EnemyBase>;
	EnemyRef _leader;
	std::vector<EnemyRef> _members;
public:
	explicit Flock(EnemyRef leader);
	void AddMember(const EnemyRef newMember);
	void RemoveFarMembers();
	void Update(float time);
	void Draw();
};


#endif //SHOOTER_FLOCK_H
