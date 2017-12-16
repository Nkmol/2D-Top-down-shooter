//
// Created by Ahmad Rahimi on 11/21/17.
//

#ifndef SHOOTER_ENEMYBASE_H
#define SHOOTER_ENEMYBASE_H

#include <memory>
#include "Point.h"
#include "MoveableObject.h"
#include <json.hpp>
#include "Player.h"
#include "Helper.h"
#include "PhysicsManager.h"

class IAIBase;

class EnemyBase : public MoveableObject {

protected:
	// TODO share same AI parts (shared_ptr)
	std::unique_ptr<IAIBase> _behaviour;

	int lifepoints, damage, reward;
	Point destinationPoint;

	const int getLifepoints() const;
	const int changeLifepoints(const int lp);
	const int getDamage() const;
	const int getReward() const;
	void onBaseCollision(MoveableObject * object);
	void onBaseCollision(GameObject * object);
	void onCollision(MoveableObject * object);
	void onCollision(Bullet * bullet);
	void onCollision(EnemyBase * enemy);
	void onCollision(Player * player);
	void onBaseCollision(bool isWall);

public:
	EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward = 50);
	EnemyBase(const std::string& filePath, const Point& coordinates, const float speed, const bool isLeader,
		const int damage, const int lifepoints, const int reward);
	EnemyBase(const nlohmann::json & j, std::vector<std::unique_ptr<EnemyBase>>* npcList, std::shared_ptr<Player> player);
	EnemyBase(const EnemyBase& other);
	virtual ~EnemyBase();

	void UpdatePosition(const float time);

	void ApplyForce(float forcePower, int forceDirection);

	//getters
	const Point& GetDestinationPoint() const;
	IAIBase& GetBehaviour() const;

	//setters
	void SetDestination(const Point& point);
	void SetDestinationPoint(const Point& point);

	void update(const float time);
	void draw();

	std::vector<std::unique_ptr<EnemyBase>>* npcs;
	std::shared_ptr<Player> _player;
	std::unique_ptr<Point> Position;
	std::unique_ptr<Point> Acceleration;
	std::unique_ptr<Point> Velocity;
	std::unique_ptr<Point> Seperation;
	std::unique_ptr<Point> Cohesion;
	std::unique_ptr<Point> Alignment;
	std::unique_ptr<Point> SepPlayer;

	const float RADIUS = 60.0f;
	const float NEIGHBOUR_RADIUS = 60.0f;
	const float SEPERATION_RADIUS = 25.0f;
	const float MAX_FORCE = 0.05f;
	const float MAX_SPEED = 1.0f;
};


#endif //SHOOTER_ENEMYBASE_H