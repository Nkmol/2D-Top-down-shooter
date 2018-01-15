//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include "Player.h"
#include "Bullet.h"

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
    for (auto &weapon : wp) {
        _weapons.push_back(weapon);
    }
}

void Player::SetWeapons(const std::vector<Weapon> wp) {
    _weapons = wp;
}

int Player::GetCurrentWeaponIndex() const {
    return currentWeapon;
}

void Player::ChangeWeapon(const unsigned index) {
    if (index >= _weapons.size() || index < 0) {
        return;
    }

    currentWeapon = index;
}

bool Player::IsCheatActive() {
	return _isCheatActive;
}

Bullet Player::shoot() {
	GetWeapon()->ResetLastShot();
	return GetWeapon()->GetBullet(GetAngle(), _coordinates, _isCheatActive);
}

bool Player::CanShoot() {
    return GetWeapon()->CanShoot();
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

Weapon *Player::GetWeapon() {
    return &_weapons[currentWeapon];
}

const vector<Weapon> &Player::GetWeapons() const {
    return _weapons;
}

void to_json(nlohmann::json &j, const Player &value) {
    j = nlohmann::json{
            {"lifepoints",    value.GetLifepoints()},
            {"highestLevel",  value.GetHighestLevel()},
            {"weapons",       value.GetWeapons()},
            {"currentWeapon", value.GetCurrentWeaponIndex()}
    };
}

void from_json(const nlohmann::json &j, Player &value) {
    value.ChangeLifepoints(j.at("lifepoints").get<int>());
    value.ChangeWeapon(j.at("currentWeapon").get<int>());
    value.SetHighestLevel(j.at("highestLevel").get<int>());

    // TODO resolve with wep id -> refactored when weapons are saved in JSON
    auto weps = value.GetWeapons();
    auto jsonWeapons = j.at("weapons");
    for (auto i = 0; i < jsonWeapons.size(); i++) {
        from_json(jsonWeapons[i], weps[i]);
    }

    value.SetWeapons(weps);
}

void Player::OnBaseCollision(bool isCollidedOnWall) {
    MoveableObject::StopMove();
}

void Player::Hit(int _damage) {
	if (_isCheatActive) return;
	
	auto hittime = clock();
	if (difftime((time_t)hittime, (time_t)_lastHit) >= _invTime)
	{
		_lastHit = hittime;
		_lifepoints -= _damage;
		if (_lifepoints <= 0) {
			_lifepoints = 0;
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
