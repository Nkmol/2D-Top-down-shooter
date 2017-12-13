//
// Created by Mevlüt Özdemir on 09-11-17.
//

#include "Player.h"
#include "Bullet.h"

Player::Player(const std::string &filePath, const float x, const float y)
        : Player(filePath, Point{x, y})
{
	_type = PLAYER;
}

Player::Player(const std::string &filePath, const Point coordinates, const int lp)
	: MoveableObject(filePath, coordinates, 140.0f), currentWeapon(0), lifepoints(lp)
{
	_type = PLAYER;
}

void Player::addWeapons(std::vector<Weapon> wp) {
    for (auto &weapon : wp) {
        weapons.push_back(weapon);
    }
}

void Player::SetWeapons(const std::vector<Weapon> wp) {
	weapons = wp;
}

int Player::getCurrentWeaponIndex() const
{
	return currentWeapon;
}

void Player::changeWeapon(const unsigned index) {
	if(index >= weapons.size() || index < 0)
	{
		return;
	}

	currentWeapon = index;
}

Bullet Player::shoot() {
    return getWeapon()->getBullet(getAngle(), _coordinates);
}

void Player::Move(const Point direction) {
    _destination = direction;
}

void Player::update(float time) {

	const auto newPostition = _coordinates + (_destination * speed * time);
	PhysicsManager::Instance().checkWallCollision(this, newPostition);
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

const vector<Weapon>& Player::getWeapons() const
{
	return weapons;
}

void to_json(nlohmann::json& j, const Player& value)
{
	j = nlohmann::json{
		{ "lifepoints", value.getLifepoints() },
		{ "highestLevel", value.GetHighestLevel() },
		{ "weapons",  value.getWeapons() },
		{ "currentWeapon", value.getCurrentWeaponIndex() }
	};
}

void from_json(const nlohmann::json& j, Player& value)
{
	value.changeLifepoints(j.at("lifepoints").get<int>());
	value.changeWeapon(j.at("currentWeapon").get<int>());
	value.SetHighestLevel(j.at("highestLevel").get<int>());

	// TODO resolve with wep id -> refactored when weapons are saved in JSON
	auto weps = value.getWeapons();
	auto jsonWeapons = j.at("weapons");
	for (auto i = 0; i < jsonWeapons.size(); i++)
	{
		from_json(jsonWeapons[i], weps[i]);
	}

	value.SetWeapons(weps);
}

void Player::onBaseCollision(bool isCollidedOnWall)
{
	MoveableObject::stopMove();
}

void Player::Hit(int damage) {
	lifepoints -= damage;

	if (lifepoints) {

	}
}

void Player::HandleAnimationFinished() {
	MoveableObject::HandleAnimationFinished();
	this->SetState("idle");
}

void Player::SetState(const string &_state) {
	// so the state will not change when
	MoveableObject::SetState(_state);

	if (_state == "idle") {
		_frames = 20;
		tempAnimationTimer = 0.05f;
	}

	if (_state == "shoot") {
		_frames = 3;
		tempAnimationTimer = 0.05f;
	}

	if (_state == "reload") {
		this->getWeapon()->Reload();
		_frames = 20;
		tempAnimationTimer = 0.02f;
	}
}

string Player::getAnimationToken() {
	return this->spriteToken + "/" + this->getWeapon()->getName();
}