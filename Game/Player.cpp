//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include "Player.h"
#include "Bullet.h"
#include "AudioManager.h"
#include "Shotgun.h"
#include "Rifle.h"
#include "Handgun.h"

Player::Player(const std::string &filePath, const float x, const float y) :
        Player(filePath, Point{x, y}) {
}

Player::Player(const std::string &filePath, const Point coordinates, const int lp) :
        _isCheatActive{false},
        MoveableObject(filePath, coordinates, 140.0f), currentWeapon(0), _lifepoints(lp), _maxLifepoints(lp) {
    type = PLAYER;
    this->ChangeState("idle");
}

Player::~Player() = default;

void Player::AddWeapons(std::vector<Weapon> wp) {
    _weapons.emplace_back(std::make_unique<Handgun>(Handgun()));
	_weapons.emplace_back(std::make_unique<Rifle>(Rifle()));
	_weapons.emplace_back(std::make_unique<Shotgun>(Shotgun()));
}

void Player::SetWeapons(const std::vector<Weapon> wp) {
	//_weapons.clear();
	//for (auto &weapon : wp) {
	//	_weapons.push_back(std::make_unique<Weapon>(weapon));
	//}
}

int Player::GetCurrentWeaponIndex() const {
    return currentWeapon;
}

void Player::ChangeWeapon(const unsigned index) {
    if (index >= _weapons.size() || index < 0) {
        return;
    }
	AudioManager::Instance().PlayEffect("switchweapon");
    currentWeapon = index;
}

bool Player::IsCheatActive() {
	return _isCheatActive;
}

std::vector<Bullet> Player::Shoot() {
	GetWeapon()->ResetLastShot();

	float x = -28;
	float y = -11;

	float radians = angle * M_PI / 180;
	float newx = x * cos(radians) - y * sin(radians);
	float newy = x * sin(radians) + y * cos(radians);
	
	//float(GetMidX()), float(GetMidY())
	return GetWeapon()->GetBullet(angle, { GetMidX() + newx, GetMidY() + newy }, _isCheatActive);
}

bool Player::CanShoot() {
    return GetWeapon()->CanShoot();
}

int Player::GetPoints() const
{
	return _points;
}

void Player::AddPoints(const int value)
{
	_points += value;
}

void Player::Move(const Point direction) {
    destination = direction;
}

void Player::Update(float time) {
    GetWeapon()->UpdateFireRate(time);
    UpdatePowerups(time);
    const auto newPosition = _coordinates + (destination * speed * time);
    PhysicsManager::Instance().CheckWallCollision(this, newPosition);
    PhysicsManager::Instance().CheckNewStaticObjectCollision(this, newPosition);
    MoveableObject::Update(time);
}

const int Player::GetLifepoints() const {
    return _lifepoints;
}

const int Player::ChangeLifepoints(const int lp) {
    if((_lifepoints+lp) >= 100)
        _lifepoints = 100;
    else
        _lifepoints += lp;
    return _lifepoints;
}

Weapon* Player::GetWeapon() {
    return _weapons[currentWeapon].get();
}

const std::vector<std::unique_ptr<Weapon>>& Player::GetWeapons() const {
    return _weapons;
}

void to_json(nlohmann::json &j, const Player &value) {
    j = nlohmann::json{
            {"highestLevel",  value.GetHighestLevel()}
    };
}

void from_json(const nlohmann::json &j, Player &value) {
    //value.SetMaxLifepoints(j.at("lifepoints").get<int>());
    //value.ChangeWeapon(j.at("currentWeapon").get<int>());
    value.SetHighestLevel(j.at("highestLevel").get<int>());

    // TODO resolve with wep id -> refactored when weapons are saved in JSON
    /*auto weps = value.GetWeapons();
    auto jsonWeapons = j.at("weapons");
    for (auto i = 0; i < jsonWeapons.size(); i++) {
        from_json(jsonWeapons[i], weps[i]);
    }

    value.SetWeapons(weps);*/
}

void Player::OnBaseCollision(bool isCollidedOnWall) {
    MoveableObject::StopMove();
}

void Player::Hit(int _damage) {
	if (_isCheatActive) return;
    if (_lastHit.GetTimePassed() >= _invTime)
	{
		_lastHit = Timer();
		_lifepoints -= _damage;
		if (_lifepoints <= 0) {
			_lifepoints = 0;
			AudioManager::Instance().PlayEffect("wasted");
			this->ChangeState("dead");
		}
	}
}

void Player::HandleAnimationFinished() {
    MoveableObject::HandleAnimationFinished();
    this->ChangeState("idle");
}

void Player::ChangeState(const string &state) {
    if (state == "idle") {
        IdleState();
    }

    if (state == "shoot") {
        ShootState();
    }

    if (state == "reload") {
        ReloadState();
    }

	if (state == "dead") {
		DeadState();
	}
}

void Player::DeadState()
{
	MoveableObject::ChangeState("dead");
}

void Player::IdleState() {
    MoveableObject::ChangeState("idle");
    frames = 20;
    animationTimer = 0.05f; // fix;
}


void Player::ShootState() {
    if (GetWeapon()->HasBullets()) {
        MoveableObject::ChangeState("shoot");
        frames = 3;
        animationTimer = 0.05f;
    }
}

void Player::ReloadState() {
    if (this->GetWeapon()->CanReload()) {

        MoveableObject::ChangeState("reload");

        this->GetWeapon()->Reload();
        frames = 20;

        // todo: fix, reload for handgun is 15 frames
        if (this->GetWeapon()->GetType() == "handgun") {
            frames = 15;
        }

        animationTimer = 0.02f;
    }
}

// a player doesnot have his own image, it's based on the weapon.
string Player::GetAnimationToken() {
    return this->_spriteToken + "/" + this->GetWeapon()->GetType();
}

void Player::UpdatePowerups(float time) {
    int i = 0;
    std::vector<int> ids;
    for( std::unique_ptr<PowerupMode> &powerup : powerupmodes){
        if(powerup->GetCounter() >= powerup->GetMaxTime()){
            ids.emplace_back(i);
        }else{
            powerup->Update(time, *this);
        }
        i++;
    }
    for(auto id : ids){
        powerupmodes.erase(powerupmodes.begin() + id);
    }
}

void Player::ToggleCheats() {
    _isCheatActive = !_isCheatActive;
}
