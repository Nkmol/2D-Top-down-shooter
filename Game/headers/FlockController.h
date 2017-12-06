//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_FLOCKCONTROLLER_H
#define SHOOTER_FLOCKCONTROLLER_H


#include "Player.h"
#include "Flock.h"
#include "memory"
#include "vector"

class FlockController
{
	vector<unique_ptr<Flock>> _flocks;
public:
	FlockController() = default;
	template <class T>
	void GenerateFlock(int flockSize, int minPos, int maxPos, Player& flockTarget, std::vector<unique_ptr<GameObject>> &gameObjects);
	void DrawFlocks();
	void UpdateFlocks(float time);
};

#endif //SHOOTER_FLOCKCONTROLLER_H
