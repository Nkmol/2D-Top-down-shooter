//
// Created by Ahmad Rahimi on 11/29/17.
//

#include "ZombieEnemy.h"

namespace Properties
{
	const float AttrSpeed = 50.0f;
	const int AttrDmg = 12;
	const int AttrLp = 100;
	const int AttrReward = 8;
	const int WeightMultiplier = 100;
}

ZombieEnemy::ZombieEnemy(const Point& coordinates, const bool isLeader) : EnemyBase(
	"zombieenemy", coordinates, Properties::AttrSpeed, isLeader, Properties::AttrDmg,
	Properties::AttrLp, Properties::AttrReward)
{
	//this->weightMultiplier = Properties::WeightMultiplier;
}
