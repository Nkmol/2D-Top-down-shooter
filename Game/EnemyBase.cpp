//
// Created by Ahmad Rahimi on 11/21/17.
//
#include "EnemyBase.h"
#include "IAIBase.h"
#include "AIDefault.h"
#include "FactoryBehaviour.h"
#include "Bullet.h"

EnemyBase::EnemyBase(const std::string &filePath, const float xPos, const float yPos, const float speed,
                     const bool isLeader, const int damage, const int lifepoints, const int reward) :
        EnemyBase(filePath, Point{xPos, yPos}, speed, isLeader, damage, lifepoints, reward) {
    _type = ENEMY;
}

EnemyBase::EnemyBase(const std::string &filePath, const Point &coordinates, const float speed, const bool isLeader,
                     const int damage, const int lifepoints, const int reward) :
        MoveableObject(filePath, coordinates, speed),
        _behaviour(make_unique<AIDefault>(*this, 100, isLeader)),
        lifepoints(lifepoints),
        damage(damage),
        reward(reward),
        destinationPoint{coordinates} {
    _type = ENEMY;
}

EnemyBase::EnemyBase(const nlohmann::json &j) : EnemyBase{j.at("type").get<string>(),
                                                          Point(0, 0),
                                                          j.at("speed").get<int>(),
                                                          false,
                                                          j.at("damage").get<int>(),
                                                          j.at("lifepoints").get<int>(),
                                                          j.at("reward").get<int>()} {
    auto a = FactoryBehaviour::Instance().Create(j.at("behaviour").get<std::string>());
    a->SetWeightMultiplier(j.at("weightmultiplier").get<int>());
    _behaviour = move(a);
    _type = ENEMY;
}


EnemyBase::EnemyBase(const EnemyBase &other) : MoveableObject(other),
                                               _behaviour(other._behaviour->Clone()),
                                               lifepoints(other.lifepoints),
                                               damage(other.damage), reward(other.reward),
                                               destinationPoint(other._coordinates) {
    _behaviour->SetOwner(*this);
    _type = ENEMY;
}

EnemyBase::~EnemyBase() = default;

void EnemyBase::ApplyForce(const float forcePower, const int forceDirection) {
    const auto forceX = float(forcePower * cos(forceDirection));
    const auto forceY = float(forcePower * sin(forceDirection));
    this->destinationPoint.x += forceX;
    this->destinationPoint.y += forceY;
}

void EnemyBase::UpdatePosition(std::vector<weak_ptr<EnemyBase>>& others, const float time)
{
	_behaviour->Update(others, time);
    update(time);
}

void EnemyBase::update(const float time) {
    const auto newPostition = _coordinates + (_destination * speed * time);
    //PhysicsManager::Instance().CheckQuadTreeCollision(this, newPostition);

    PhysicsManager::Instance().checkWallCollision(this, newPostition);
    PhysicsManager::Instance().checkMoveableCollision(this, newPostition);
    MoveableObject::update(time);
}

const Point &EnemyBase::GetDestinationPoint() const {
    return destinationPoint;
}

IAIBase &EnemyBase::GetBehaviour() const {
    return *_behaviour;
}

void EnemyBase::SetDestinationPoint(const Point &point) {
    destinationPoint = point;
}

void EnemyBase::SetDestination(const Point &point) {
    _destination = point;
}

const int EnemyBase::getLifepoints() const {
    return lifepoints;
}

const int EnemyBase::changeLifepoints(const int lp) {
    lifepoints += lp;
    return lifepoints;
}

const int EnemyBase::getDamage() const {
    return damage;
}

const int EnemyBase::getReward() const {
    return reward;
}

void EnemyBase::onBaseCollision(MoveableObject *object) {
    switch (object->getType()) {
        case BULLET:
            onCollision(dynamic_cast<Bullet *>(object));
            break;
        case ENEMY:
            onCollision(dynamic_cast<EnemyBase *>(object));
            break;
        case PLAYER:
            onCollision(dynamic_cast<Player *>(object));
            break;
        default:
            break;
    }
}

void EnemyBase::onBaseCollision(GameObject *object) {

}

void EnemyBase::onCollision(MoveableObject *object) {
    MoveableObject::stopMove();
}

void EnemyBase::onCollision(Bullet *bullet) {
    lifepoints -= bullet->getDamage();
    if (lifepoints < 0) {
        hide();
    }

    bullet->onBaseCollision(true);

    MoveableObject::stopMove();
}

void EnemyBase::onCollision(EnemyBase *enemy) {
    MoveableObject::stopMove();
}

void EnemyBase::onCollision(Player *player) {
    player->Hit(damage);
    MoveableObject::stopMove();
}

void EnemyBase::onBaseCollision(bool isWall) {
    MoveableObject::stopMove();
}