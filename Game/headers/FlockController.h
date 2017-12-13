//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_FLOCKCONTROLLER_H
#define SHOOTER_FLOCKCONTROLLER_H


#include <memory>
#include <vector>
#include <GameObject.h>

class EnemyBase;
class Player;
class Flock;
class MoveableObject;

class FlockController
{
	std::vector<std::unique_ptr<Flock>> _flocks;
public:
	FlockController();
	~FlockController();
	void GenerateFlock(const EnemyBase& basedOn, const int flockSize, const int minPos, const int maxPos,
	                   Player& flockTarget, std::vector<std::shared_ptr<GameObject>>& gameObjects);
	void DrawFlocks();
	void UpdateFlocks(float time);
};

#endif //SHOOTER_FLOCKCONTROLLER_H
