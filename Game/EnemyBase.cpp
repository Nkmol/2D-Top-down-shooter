//
// Created by Ahmad Rahimi on 11/21/17.
//
#include "EnemyBase.h"

namespace enemybase_constants {
    const int COLLIDABLEWEIGHTMULTIPLIER = 100000;
}

EnemyBase::EnemyBase(const std::string &filePath, Point coordinates, float speed, bool isLeader, int damage,
                     int lifepoints, int reward) :
        MoveableObject("enemy", filePath, coordinates, speed, damage),
        destinationPoint{coordinates.x, coordinates.y},
        isLeader{isLeader},
        lifepoints(lifepoints),
        reward(reward) {
}


void EnemyBase::Align() {
    destinationPoint = _leader->destinationPoint;
}

void EnemyBase::UpdatePositions(float time) {
    if (!isLeader) {
        massCenter = Point(0, 0);
        massSize = 0;
        std::vector<GameObject> neighbours = PhysicsManager::Instance().RetrieveNearbyGameObjects(*this);
        Align();
        for (auto &other: neighbours) {
            Cohese(other);
            //apply cohesion force
            massCenter = massCenter / massSize;
            Seperate(other);
        }
        const auto forceDirection = Helper::calculateAngle(_coordinates.x, _coordinates.y, massCenter.x, massCenter.y);
        ApplyForce(0.1, forceDirection);

    } else {
        GoTarget();
    }

    //calculate destinationpoint after all forces are applied
    const auto rad = (atan2(_coordinates.y - destinationPoint.y, _coordinates.x - destinationPoint.x));
    const auto dir = Helper::radiansToDegrees(rad);
    const auto correctedAngleRadians = Helper::degreesToRadians(dir - 90);
    SetAngle(dir);

    _destination = Point(sin(correctedAngleRadians), -cos(correctedAngleRadians));
    update(time);
}

void EnemyBase::Cohese(GameObject &other) {
    if (other.GetId() != this->GetId()) {
        if (other.GetTeamId() == this->GetTeamId()) {
            const auto &oCoordinates = other.GetCoordinates();
            massCenter += oCoordinates;
        }
    }
}

void EnemyBase::Seperate(GameObject &other) {
    if (other.GetId() != this->GetId()) {
        //teamid -100 are collidables
        const auto &oWeight = other.getWidth() * other.getHeight() * (other.GetTeamId() != -100 ? weightMultiplier
                                                                                                : enemybase_constants::COLLIDABLEWEIGHTMULTIPLIER);
        const auto &oCoordinates = other.GetCoordinates();
        const Point squared((oCoordinates.x - _coordinates.x) * (oCoordinates.x - _coordinates.x),
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

void EnemyBase::ApplyForce(const float forcePower, const int forceDirection) {
    const auto forceX = float(forcePower * cos(forceDirection));
    const auto forceY = float(forcePower * sin(forceDirection));
    this->destinationPoint.x += forceX;
    this->destinationPoint.y += forceY;
}

void EnemyBase::GoTarget() {
    this->destinationPoint = _target->GetCoordinates();
}

const Player &EnemyBase::getTarget() const {
    return *_target;
}

void EnemyBase::setTarget(const Player &target) {
    EnemyBase::_target = &target;
}

void EnemyBase::setLeader(const EnemyBase &leader) {
    EnemyBase::_leader = &leader;
}

void EnemyBase::update(float time) {
    if (!PhysicsManager::Instance().checkCollision(getMidX(_coordinates.x + _destination.x * speed * time),
                                                   getMidY(_coordinates.y + _destination.y * speed * time),
                                                   getRadius())) {
        MoveableObject::update(time);
    } else {
        MoveableObject::stopMove();
    }
}

void EnemyBase::draw() {
    MoveableObject::draw();
}

const int EnemyBase::getLifepoints() const {
    return lifepoints;
}

const int EnemyBase::changeLifepoints(const int lp) {
    lifepoints += lp;
    return lifepoints;
}

//const int EnemyBase::getDamage() const {
//    return damage;
//}

const int EnemyBase::getReward() const {
    return reward;
}

void EnemyBase::onCollision(GameObject object) {
    if (object.GetName() == "bullet") {
        this->lifepoints -= object.getDamage();

        if (this->getLifepoints()) {
            this->hide(); // todo: hide or something else
        }
    }
}
