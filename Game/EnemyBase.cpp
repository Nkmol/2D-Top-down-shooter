//
// Created by Ahmad Rahimi on 11/21/17.
//

#include "EnemyBase.h"

EnemyBase::EnemyBase(const std::string &filePath, float xPos, float yPos, float speed, bool isLeader, int damage, int lifepoints, int reward) :
		MoveableObject(filePath, xPos, yPos, speed),
		isLeader{isLeader},
		destinationPoint{xPos, yPos},
		damage(damage),
		lifepoints(lifepoints),
		reward(reward) {
//    angle = 0;
}

void EnemyBase::updatePositions(std::vector<shared_ptr<EnemyBase>> others, float time) {
    if (!isLeader) {
        align();
        cohese(others);
        seperate(others);
    } else {
        goTarget();
    }

    float _rad = (atan2(this->getYPos() - destinationPoint.y, this->getXPos() - destinationPoint.x));
    float _dir = Helper::radiansToDegrees(_rad);
    float correctedAngleRadians = Helper::degreesToRadians(_dir - 90);
    this->setAngle(_dir);
    this->destinationXPos = speed * sin(correctedAngleRadians);
    this->destinationYPos = speed * -cos(correctedAngleRadians);
    this->update(time);
}

void EnemyBase::align() {
    this->destinationPoint = this->leader->destinationPoint;
}

void EnemyBase::cohese(std::vector<shared_ptr<EnemyBase>> others) {
    Point massCenter = Point(0, 0);
    for (auto const &other: others) {
        if (other.get() != shared_from_this().get()) {
            massCenter.x += other->getXPos();
            massCenter.y += other->getYPos();
        }
    }

    auto othersSize = others.size() - 1;
    massCenter.x = massCenter.x / othersSize;
    massCenter.y = massCenter.y / othersSize;
    int forceDirection = Helper::calculateAngle(this->getXPos(), this->getYPos(), massCenter.x, massCenter.y);
    this->applyForce(0.1, forceDirection);
}

void EnemyBase::seperate(std::vector<shared_ptr<EnemyBase>> others) {
    for (auto const &other: others) {
        if (other.get() != shared_from_this().get()) {
            Point squared = Point((other->getXPos() - this->getXPos()) * (other->getXPos() - this->getXPos()),
                                  (other->getYPos() - this->getYPos()) * (other->getYPos() - this->getYPos()));
            float squareDist = squared.x + squared.y;
            if (squareDist < 155500) {
                Point headingVector = Point(this->getXPos() - other->getXPos(), this->getYPos() - other->getYPos());
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
    this->destinationPoint = Point(target->getXPos(), target->getYPos());
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
