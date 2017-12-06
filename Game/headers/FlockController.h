//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_FLOCKCONTROLLER_H
#define SHOOTER_FLOCKCONTROLLER_H


#include <memory>
#include <vector>

class EnemyBase;
class Player;
class Flock;

class FlockController
{
	std::vector<std::unique_ptr<Flock>> _flocks;
public:
	FlockController();
	~FlockController();
	void GenerateFlock(const EnemyBase& basedOn, const int flockSize, const int minPos, const int maxPos,
	                   Player& flockTarget);
	void DrawFlocks();
	void UpdateFlocks(float time);
};

#endif //SHOOTER_FLOCKCONTROLLER_H
