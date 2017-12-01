//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "EnemyBase.h"

EnemyBase::EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward) :
		MoveableObject(filePath, Point{ xPos, yPos }, speed),
		destinationPoint{xPos, yPos},
		isLeader{isLeader},
		lifepoints(lifepoints),
		damage(damage),
		reward(reward) {
//    angle = 0;
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

void EnemyBase::updatePositions(std::vector<shared_ptr<EnemyBase>> others, float time) {
    if (!isLeader) {
        align();
        cohese(others);
        seperate(others);
    } else {
        goTarget();
    }

    float _rad = (atan2(_coordinates.y - destinationPoint.y, _coordinates.x - destinationPoint.x));
    float _dir = Helper::radiansToDegrees(_rad);
    float correctedAngleRadians = Helper::degreesToRadians(_dir - 90);
    this->setAngle(_dir);

	_destination = Point(sin(correctedAngleRadians), -cos(correctedAngleRadians));

	this->update(time);
}

void EnemyBase::align() {
    this->destinationPoint = this->leader->destinationPoint;
}

void EnemyBase::cohese(std::vector<shared_ptr<EnemyBase>> others) {
    Point massCenter = Point(0, 0);
    for (auto const &other: others) {
        if (other.get() != shared_from_this().get()) {
			const auto& oCoordinates = other->GetCoordinates();
            massCenter.x += oCoordinates.x;
            massCenter.y += oCoordinates.y;
        }
    }

    auto othersSize = others.size() - 1;
    massCenter.x = massCenter.x / othersSize;
    massCenter.y = massCenter.y / othersSize;
    int forceDirection = Helper::calculateAngle(_coordinates.x, _coordinates.y, massCenter.x, massCenter.y);
    this->applyForce(0.1, forceDirection);
}

void EnemyBase::seperate(std::vector<shared_ptr<EnemyBase>> others) {
    for (auto const &other: others) {
        if (other.get() != shared_from_this().get()) {
			const auto& oCoordinates = other->GetCoordinates();
            Point squared = Point((oCoordinates.x - _coordinates.x) * (oCoordinates.x - _coordinates.x),
                                  (oCoordinates.y - _coordinates.y) * (oCoordinates.y - _coordinates.y));
            float squareDist = squared.x + squared.y;
            if (squareDist < 155500) {
                Point headingVector = Point(_coordinates.x - oCoordinates.x, _coordinates.y - oCoordinates.y);
                double scale = sqrt(squareDist) / sqrt(155500);
                Point unitVector = Point(headingVector.x / sqrt(squareDist), headingVector.y / sqrt(squareDist));
                Point scaledVector = Point((unitVector.x / scale), (unitVector.y / scale));
                this->destinationPoint.x += scaledVector.x;
                this->destinationPoint.y += scaledVector.y;
            }
        }
    }
}

void EnemyBase::applyForce(float forcePower, int forceDirection) {
    auto forceX = float(forcePower * cos(forceDirection));
    auto forceY = float(forcePower * sin(forceDirection));
    this->destinationPoint.x += forceX;
    this->destinationPoint.y += forceY;
}

void EnemyBase::goTarget() {
	const auto& tCoordinates = target->GetCoordinates();
    this->destinationPoint = Point(tCoordinates.x, tCoordinates.y);
}

const shared_ptr<Player> &EnemyBase::getTarget() const {
    return target;
}

void EnemyBase::setTarget(const shared_ptr<Player> &target) {
    EnemyBase::target = target;
}

void EnemyBase::setLeader(const shared_ptr<EnemyBase> &leader) {
    EnemyBase::leader = leader;
}

void EnemyBase::update(float time) {
	if (!PhysicsManager::Instance().checkOuterWallCollision(getMidX(_coordinates.x + _destination.x * speed * time), getMidY(_coordinates.y + _destination.y * speed * time), getRadius())) {
		MoveableObject::update(time);
	}
	else {
		MoveableObject::stopMove();
	}

    
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
