//
// Created by Ahmad Rahimi on 11/21/17.
//
#include "EnemyBase.h"
#include "IAIBase.h"
#include "AIDefault.h"
#include "FactoryBehaviour.h"
#include "Bullet.h"
#include "powerups/PowerupHP.h"
#include "powerups/DropableFactory.h"
#include "Level.h"
#include "powerups/PowerupFastShot.h"
#include "AudioManager.h"

EnemyBase::EnemyBase(const std::string &filePath, const float xPos, const float yPos, const float speed,
	const bool isLeader, const int _damage, const int lifepoints, const int reward, float multiplier) :
        EnemyBase(filePath, Point{xPos, yPos}, speed, isLeader, _damage, lifepoints, reward, multiplier) {
    type = ENEMY;
}

EnemyBase::EnemyBase(const std::string &filePath, const Point &coordinates, const float speed, const bool isLeader,
                     const int _damage, const int lifepoints, const int reward, float multiplier) :
        MoveableObject(filePath, coordinates, speed*multiplier),
        _behaviour(make_unique<AIDefault>(*this, 100* multiplier, isLeader)),
        lifepoints(lifepoints*multiplier),
        _damage(_damage*multiplier),
        reward(reward*multiplier),
        destinationPoint{coordinates} {
    type = ENEMY;
}

EnemyBase::EnemyBase(const nlohmann::json &j, std::vector<std::unique_ptr<EnemyBase>>* npcList, std::shared_ptr<Player> player) : EnemyBase{j.at("type").get<string>(),
                                                          Point(0, 0),
                                                          j.at("speed").get<int>(),
                                                          false,
                                                          j.at("damage").get<int>(),
                                                          j.at("lifepoints").get<int>(),
                                                          j.at("reward").get<int>()} {
    auto a = FactoryBehaviour::Instance().Create(j.at("behaviour").get<std::string>());
    a->SetWeightMultiplier(j.at("weightmultiplier").get<int>());
    _behaviour = move(a);
    type = ENEMY;
	_behaviour->SetOwner(*this);
	npcs = { npcList };
	_player = { player };
}


EnemyBase::EnemyBase(const EnemyBase &other) : MoveableObject(other),
                                               _behaviour(other._behaviour->Clone()),
                                               lifepoints(other.lifepoints),
                                               _damage(other._damage), reward(other.reward),
                                               destinationPoint(other._coordinates) {
    _behaviour->SetOwner(*this);
    type = ENEMY;
}

EnemyBase::~EnemyBase() = default;

void EnemyBase::ApplyForce(const float forcePower, const int forceDirection) {
    const auto forceX = float(forcePower * cos(forceDirection));
    const auto forceY = float(forcePower * sin(forceDirection));
    this->destinationPoint.x += forceX;
    this->destinationPoint.y += forceY;
}

void EnemyBase::UpdatePosition(const float time)
{
	_behaviour->Update(time);
    Update(time);
}

void EnemyBase::Update(const float time) {
    const auto newPostition = _coordinates + (destination * speed * time);


    PhysicsManager::Instance().CheckNewStaticObjectCollision(this, newPostition);
    PhysicsManager::Instance().CheckMoveableCollision(this, newPostition);
    MoveableObject::Update(time);
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
    destination = point;
}

const int EnemyBase::GetLifepoints() const {
    return lifepoints;
}

const int EnemyBase::ChangeLifepoints(const int lp) {
    lifepoints += lp;
    return lifepoints;
}

const int EnemyBase::GetDamage() const {
    return _damage;
}

const int EnemyBase::GetReward() const {
    return reward;
}

void EnemyBase::OnBaseCollision(MoveableObject *object) {
    switch (object->GetType()) {
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

void EnemyBase::OnBaseCollision(GameObject *object) {

}

void EnemyBase::onCollision(MoveableObject *object) {
    MoveableObject::StopMove();
}

void EnemyBase::onCollision(Bullet *bullet) {
    lifepoints -= bullet->GetDamage();
	AudioManager::Instance().PlayEffect("hitmarker");
    if (lifepoints < 0) {
        dropDropable();
		AudioManager::Instance().PlayEffect("enemydie");
        Hide();
    }

    bullet->OnBaseCollision(true);

    MoveableObject::StopMove();
}

void EnemyBase::onCollision(EnemyBase *enemy) {
    MoveableObject::StopMove();
}

void EnemyBase::onCollision(Player *player) {
    player->Hit(_damage);
    MoveableObject::StopMove();
}

void EnemyBase::dropDropable() {
    int dropchance = DropableFactory::Instance().dropChance;
    int hp = 1;
    int fastshoot = 2;
    int rollNumber = rand() % 10 + 0;
    if(rollNumber <= dropchance){

        if(rollNumber == 1){
            PowerupHP powerup = PowerupHP(_coordinates);
            Level::_loot.emplace_back(make_unique<PowerupHP>(powerup));
        }else{
            PowerupFastShot powerup = PowerupFastShot(_coordinates);
            Level::_loot.emplace_back(make_unique<PowerupFastShot>(powerup));
        }
    }
}

void EnemyBase::OnBaseCollision(bool isWall) {
    MoveableObject::StopMove();
}
