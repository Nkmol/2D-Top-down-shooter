//
// Created by Ahmad Rahimi on 11/21/17.
//
#include "EnemyBase.h"

namespace enemybase_constants {
    const int COLLIDABLEWEIGHTMULTIPLIER = 10000;
}
EnemyBase::EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward) :
		MoveableObject(filePath, Point{ xPos, yPos }, speed),
		destinationPoint{xPos, yPos},
		isLeader{isLeader},
		lifepoints(lifepoints),
		damage(damage),
		reward(reward) {
	_type = ENEMY;
}

EnemyBase::EnemyBase(const std::string &filePath, Point coordinates, float speed, bool isLeader, int damage, int lifepoints, int reward) :
	MoveableObject(filePath, coordinates, speed),
	destinationPoint{ coordinates.x, coordinates.y },
	isLeader{ isLeader },
	lifepoints(lifepoints),
	damage(damage),
	reward(reward)
{
}

void EnemyBase::UpdatePositions(EnemiesType& others, const float time) {
  
	if (!isLeader) {
		Align();
		Cohese(others);
		Seperate(others);
	}
	else {
		GoTarget();
	}
	
	const auto rad = (atan2(_coordinates.y - destinationPoint.y, _coordinates.x - destinationPoint.x));
	const auto dir = Helper::radiansToDegrees(rad);
	const auto correctedAngleRadians = Helper::degreesToRadians(dir - 90);
    SetAngle(dir);

	_destination = Point(sin(correctedAngleRadians), -cos(correctedAngleRadians));
	update(time);
}

void EnemyBase::Align() {
    destinationPoint = _leader->destinationPoint;
}

void EnemyBase::Cohese(EnemiesType& others) {
    Point massCenter(0, 0);
    for (const auto& other: others) {
        if (other.get() != this) {

			const auto& oCoordinates = other->GetCoordinates();
			massCenter += oCoordinates;
        }
    }

	const auto othersSize = others.size() - 1;
	massCenter = massCenter / othersSize;
	const auto forceDirection = Helper::calculateAngle(_coordinates.x, _coordinates.y, massCenter.x, massCenter.y);
	ApplyForce(0.1, forceDirection);
}

void EnemyBase::Seperate(EnemiesType& others) {
    for (const auto& other: others) {
        if (other.get() != this) {
            const auto& oWeight = other->getWidth() * other->getHeight() * weightMultiplier;
			const auto& oCoordinates = other->GetCoordinates();
	        const Point squared ((oCoordinates.x - _coordinates.x) * (oCoordinates.x - _coordinates.x),
                                  (oCoordinates.y - _coordinates.y) * (oCoordinates.y - _coordinates.y));
	        const auto squareDist = squared.x + squared.y;
            if (squareDist < oWeight) {
	            const auto headingVector = Point(_coordinates.x - oCoordinates.x, _coordinates.y - oCoordinates.y);
	            const auto scale = sqrt(squareDist) / sqrt(oWeight);
	            const auto scaledVector = headingVector / sqrt(squareDist) / scale;
                this->destinationPoint += scaledVector;
            }
        }
    }

    for (const auto& other: *PhysicsManager::Instance().getCollidables()) {
        const auto& oX = other.getMidX();
        const auto& oY = other.getMidY();
        const auto& oWeight = other.getWidth() * other.getHeight() * enemybase_constants::COLLIDABLEWEIGHTMULTIPLIER;
        const auto& m = this->GetCoordinates();
	    const Point squared ((oX - m.x) * (oX - m.x), (oY - m.y) * (oY - m.y));
	    const auto squareDist = squared.x + squared.y;
        if(squareDist < oWeight){
	        const Point headingVector (m.x - oX, m.y - oY);
	        const auto scale = sqrt(squareDist) / sqrt(oWeight);
            const auto scaledVector = headingVector / sqrt(squareDist) / scale;
            destinationPoint += scaledVector;
        }
    }
}

void EnemyBase::ApplyForce(const float forcePower, const int forceDirection) {
	const auto forceX = float(forcePower * cos(forceDirection));
	const auto forceY = float(forcePower * sin(forceDirection));
    this->destinationPoint.x += forceX;
    this->destinationPoint.y += forceY;
}

void EnemyBase::GoTarget() {
    this->destinationPoint = _target->GetCoordinates();
}

const Player& EnemyBase::getTarget() const {
    return *_target;
}

void EnemyBase::setTarget(const Player& target) {
    EnemyBase::_target = &target;
}

void EnemyBase::setLeader(const EnemyBase& leader) {
    EnemyBase::_leader = &leader;
}

void EnemyBase::update(float time) {
	const auto newPostition = _coordinates + (_destination * speed * time);
	PhysicsManager::Instance().checkWallCollision(this, newPostition);
	PhysicsManager::Instance().checkMoveableCollision(this, newPostition);
		MoveableObject::update(time);
}

void EnemyBase::draw() {
    MoveableObject::draw();
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


void EnemyBase::onBaseCollision(shared_ptr<MoveableObject> moveableObject)
{
	onCollision(moveableObject.get());

	//switch (moveableObject.get()->getType())
	//{
	//case BULLET: dynamic_cast<Bullet*>(moveableObject.get());
	//case ENEMY:
	//case PLAYER:
	//default:
	//	break;
	//}
}

void EnemyBase::onCollision(Bullet bullet)
{
	bullet.onCollision(true);
	MoveableObject::stopMove();
}

void EnemyBase::onCollision(EnemyBase enemy)
{
	bullet.onCollision(true);
	MoveableObject::stopMove();
}