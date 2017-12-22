//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include "Player.h"
#include "Bullet.h"

Player::Player(const std::string &filePath, const float x, const float y) :
        Player(filePath, Point{x, y}) {
}

Player::Player(const std::string &filePath, const Point coordinates, const int lp) :
        isCheatActive{false},
        MoveableObject(filePath, coordinates, 140.0f), currentWeapon(0), lifepoints(lp) {
    _type = PLAYER;
    this->ChangeState("idle");
}

Player::~Player() = default;

void Player::addWeapons(std::vector<Weapon> wp) {
    for (auto &weapon : wp) {
        weapons.push_back(weapon);
    }
}

void Player::SetWeapons(const std::vector<Weapon> wp) {
    weapons = wp;
}

int Player::getCurrentWeaponIndex() const {
    return currentWeapon;
}

void Player::changeWeapon(const unsigned index) {
    if (index >= weapons.size() || index < 0) {
        return;
    }

    currentWeapon = index;
}

bool Player::IsCheatActive() {
	return isCheatActive;
}

Bullet Player::shoot() {
	getWeapon()->ResetLastShot();
	return getWeapon()->getBullet(getAngle(), _coordinates, isCheatActive);
}

bool Player::CanShoot() {
    return getWeapon()->CanShoot();
}

void Player::Move(const Point direction) {
    _destination = direction;
}

void Player::update(float time) {
    getWeapon()->UpdateFireRate(time);
    updatePowerups(time);
    const auto newPosition = _coordinates + (_destination * speed * time);
    PhysicsManager::Instance().checkWallCollision(this, newPosition);
    PhysicsManager::Instance().checkStaticObjectCollision(this, newPosition);
    MoveableObject::update(time);
}

const int Player::getLifepoints() const {
    return lifepoints;
}

const int Player::changeLifepoints(const int lp) {
    lifepoints += lp;
    return lifepoints;
}

Weapon *Player::getWeapon() {
    return &weapons[currentWeapon];
}

const vector<Weapon> &Player::getWeapons() const {
    return weapons;
}

void to_json(nlohmann::json &j, const Player &value) {
    j = nlohmann::json{
            {"lifepoints",    value.getLifepoints()},
            {"highestLevel",  value.GetHighestLevel()},
            {"weapons",       value.getWeapons()},
            {"currentWeapon", value.getCurrentWeaponIndex()}
    };
}

void from_json(const nlohmann::json &j, Player &value) {
    value.changeLifepoints(j.at("lifepoints").get<int>());
    value.changeWeapon(j.at("currentWeapon").get<int>());
    value.SetHighestLevel(j.at("highestLevel").get<int>());

    // TODO resolve with wep id -> refactored when weapons are saved in JSON
    auto weps = value.getWeapons();
    auto jsonWeapons = j.at("weapons");
    for (auto i = 0; i < jsonWeapons.size(); i++) {
        from_json(jsonWeapons[i], weps[i]);
    }

    value.SetWeapons(weps);
}

void Player::onBaseCollision(bool isCollidedOnWall) {
    MoveableObject::stopMove();
}

void Player::Hit(int damage) {
    if (!isCheatActive) {
        lifepoints -= damage;
    }
}

void Player::HandleAnimationFinished() {
    MoveableObject::HandleAnimationFinished();
    this->ChangeState("idle");
}

void Player::ChangeState(const string &_state) {
    if (_state == "idle") {
        IdleState();
    }

    if (_state == "shoot") {
        ShootState();
    }

    if (_state == "reload") {
        ReloadState();
    }
}


void Player::IdleState() {
    MoveableObject::ChangeState("idle");
    frames = 20;
    animationTimer = 0.05f; // fix;
}


void Player::ShootState() {
    if (getWeapon()->hasBullets()) {
        MoveableObject::ChangeState("shoot");
        frames = 3;
        animationTimer = 0.05f;
    }
}

void Player::ReloadState() {
    if (this->getWeapon()->CanReload()) {

        MoveableObject::ChangeState("reload");

        this->getWeapon()->Reload();
        frames = 20;

        // todo: fix, reload for handgun is 15 frames
        if (this->getWeapon()->getName() == "handgun") {
            frames = 15;
        }

        animationTimer = 0.02f;
    }
}

// a player doesnot have his own image, it's based on the weapon.
string Player::GetAnimationToken() {
    return this->spriteToken + "/" + this->getWeapon()->getName();
}

void Player::setLifepoints(int lifepoints) {
    if(lifepoints > 100)
        lifepoints = 100;
    Player::lifepoints = lifepoints;
}

void Player::updatePowerups(float time) {
    int i = 0;
    std::vector<int> ids;
    for( std::unique_ptr<PowerupMode> &powerup : powerupmodes){
        if(powerup->getCounter() >= powerup->getMaxTime()){
            ids.emplace_back(i);
        }else{
            powerup->update(time, *this);
        }
        i++;
    }
    for(auto id : ids){
        powerupmodes.erase(powerupmodes.begin() + id);
    }
}

void Player::ToggleCheats() {
    isCheatActive = !isCheatActive;
}
