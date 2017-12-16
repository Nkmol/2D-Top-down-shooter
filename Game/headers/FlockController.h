//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_FLOCKCONTROLLER_H
#define SHOOTER_FLOCKCONTROLLER_H


#include <memory>
#include <vector>

class EnemyBase;
class Player;
class MoveableObject;

class FlockController
{
public:
	FlockController();
	~FlockController();
	void GenerateFlock(const EnemyBase& basedOn, const int flockSize, const int minPos, const int maxPos,
	                   Player& flockTarget, std::vector<std::shared_ptr<MoveableObject>>& gameObjects);

};

#endif //SHOOTER_FLOCKCONTROLLER_H
