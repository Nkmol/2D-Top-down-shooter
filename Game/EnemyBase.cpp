//
// Created by Ahmad Rahimi on 11/21/17.
//
#include "EnemyBase.h"
#include "monsters/BatEnemy.h"
#include "monsters/BatEnemy.h"
#include "AIDefault.h"

EnemyBase::EnemyBase(const std::string &filePath, const float xPos, const float yPos, const float speed, const bool isLeader, const int damage, const int lifepoints, const int reward) :
	EnemyBase(filePath, Point{ xPos, yPos }, speed, isLeader, damage, lifepoints, reward)
{
}

EnemyBase::EnemyBase(const std::string &filePath, const Point coordinates, const float speed, const bool isLeader, const int damage, const int lifepoints, const int reward) :
	MoveableObject(filePath, coordinates, speed),
	_behaviour(make_unique<AIDefault>(*this, 100, isLeader)),
	lifepoints(lifepoints),
	damage(damage),
	reward(reward),
	destinationPoint{coordinates}
{
}

EnemyBase::EnemyBase(const json& j) : EnemyBase{ j.at("type").get<string>(), 
												 Point(0, 0), 
												 j.at("speed").get<int>(),
                                                 false, 
												 j.at("damage").get<int>(), 
												 j.at("lifepoints").get<int>(),
                                                 j.at("reward").get<int>() }
{
}

void EnemyBase::ApplyForce(const float forcePower, const int forceDirection) {
	const auto forceX = float(forcePower * cos(forceDirection));
	const auto forceY = float(forcePower * sin(forceDirection));
    this->destinationPoint.x += forceX;
    this->destinationPoint.y += forceY;
}

void EnemyBase::UpdatePosition(EnemiesType& others, const float time)
{
	_behaviour->Update(others, time);

	update(time);
}

void EnemyBase::update(const float time) {
	if (!PhysicsManager::Instance().checkCollision(getMidX(_coordinates.x + _destination.x * speed * time), getMidY(_coordinates.y + _destination.y * speed * time), getRadius())) {
		MoveableObject::update(time);
	}
	else {
		MoveableObject::stopMove();
	}
}

void EnemyBase::draw() {
    MoveableObject::draw();
}

const Point& EnemyBase::GetDestinationPoint() const
{
	return destinationPoint;
}

IAIBase& EnemyBase::GetBehaviour() const
{
	return *_behaviour;
}

void EnemyBase::SetDestinationPoint(const Point& point)
{
	destinationPoint = point;
}

void EnemyBase::SetDestination(const Point& point)
{
	_destination = point;
}

const int EnemyBase::getLifepoints() const
{
	return lifepoints;
}

const int EnemyBase::changeLifepoints(const int lp)
{
	lifepoints += lp;
	return lifepoints;
}

const int EnemyBase::getDamage() const
{
	return damage;
}

const int EnemyBase::getReward() const
{
	return reward;
}
