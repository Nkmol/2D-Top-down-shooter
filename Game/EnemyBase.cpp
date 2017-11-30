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

void EnemyBase::updatePositions(std::vector<unique_ptr<EnemyBase>>& others, float time) {
    if (!isLeader) {
        align();
        /*cohese(others);
        seperate(others);*/
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

void EnemyBase::cohese(std::vector<shared_ptr<EnemyBase>>& others) {
    Point massCenter(0, 0);
	//const auto sharedFromThis = shared_from_this();
    for (const auto& other: others) {
        if (other.get() != this) {

			const auto& oCoordinates = other->GetCoordinates();
			massCenter += oCoordinates;
        }
    }

    auto othersSize = others.size() - 1;
    massCenter.x = massCenter.x / othersSize;
    massCenter.y = massCenter.y / othersSize;
    int forceDirection = Helper::calculateAngle(_coordinates.x, _coordinates.y, massCenter.x, massCenter.y);
    this->applyForce(0.1, forceDirection);
}

void EnemyBase::seperate(std::vector<shared_ptr<EnemyBase>>& others) {
	//const auto sharedFromThis = shared_from_this();
    for (const auto& other: others) {
        if (other.get() != this) {
            const auto& oWeight = other->getWidth() * other->getHeight() * weightMultiplier;
			const auto& oCoordinates = other->GetCoordinates();
            Point squared ((oCoordinates.x - _coordinates.x) * (oCoordinates.x - _coordinates.x),
                                  (oCoordinates.y - _coordinates.y) * (oCoordinates.y - _coordinates.y));
            float squareDist = squared.x + squared.y;
            if (squareDist < oWeight) {
                Point headingVector = Point(_coordinates.x - oCoordinates.x, _coordinates.y - oCoordinates.y);
                double scale = sqrt(squareDist) / sqrt(oWeight);
                Point unitVector = Point(headingVector.x / sqrt(squareDist), headingVector.y / sqrt(squareDist));
                Point scaledVector = Point((unitVector.x / scale), (unitVector.y / scale));
                this->destinationPoint.x += scaledVector.x;
                this->destinationPoint.y += scaledVector.y;
            }
        }
    }

    for (GameObject const &other: *PhysicsManager::Instance().collidables) {
        const auto& oX = other.getMidX();
        const auto& oY = other.getMidY();
        const auto& oWeight = (other.getWidth() * other.getHeight()) * enemybase_constants::COLLIDABLEWEIGHTMULTIPLIER;
        const auto& mX = this->GetCoordinates().x;
        const auto& mY = this->GetCoordinates().y;
        Point squared = Point((oX - mX) * (oX - mX), (oY - mY) * (oY - mY));
        float squareDist = squared.x + squared.y;
        if(squareDist < oWeight){
            Point headingVector = Point(mX - oX, mY - oY);
            double scale = sqrt(squareDist) / sqrt(oWeight);
            Point unitVector = Point(headingVector.x / sqrt(squareDist), headingVector.y / sqrt(squareDist));
            Point scaledVector = Point((unitVector.x / scale),(unitVector.y / scale));
            this->destinationPoint.x += scaledVector.x;
            this->destinationPoint.y += scaledVector.y;
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

const Player& EnemyBase::getTarget() const {
    return *target;
}

void EnemyBase::setTarget(const Player& target) {
    EnemyBase::target = &target;
}

void EnemyBase::setLeader(const EnemyBase& leader) {
    EnemyBase::leader = &leader;
}

void EnemyBase::update(float time) {
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
