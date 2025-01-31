//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H


#include "MoveableObject.h"
#include "Weapon.h"
#include "Point.h"
#include <Weapon.h>
#include "PhysicsManager.h"
#include "../powerups/PowerupMode.h"
#include "../../Engine/Timer.h"
#include <ctime>
class Point;

class Player : public MoveableObject {

    std::vector<std::unique_ptr<Weapon>> _weapons;
    unsigned currentWeapon;
    int _lifepoints;
	int _maxLifepoints;
    int _highestLevel = 1;
	bool _isCheatActive;
	Timer _lastHit = Timer();
	double _invTime = 500;
	std::string _saveName;
    bool isCheatActive;

	int _points = 0;
public:
	std::vector<std::unique_ptr<PowerupMode>> powerupmodes;

    Player(const std::string &filePath, float x, float y);

    Player(const std::string &filePath, Point coordinates, int lp = 100);

	~Player();

    std::vector<Bullet> Shoot();

    void Move(const Point direction);

	void UpdatePowerups(float time);

    void Update(float time) override;

    const int GetLifepoints() const;

    const int ChangeLifepoints(const int lp);

	const int GetMaxLifepoints() const { return _maxLifepoints; }

	const int SetMaxLifepoints(const int lp) { _maxLifepoints = lp; return _maxLifepoints; }

    Weapon* GetWeapon();

    void ChangeWeapon(unsigned index);

	bool IsCheatActive();

    const std::vector<std::unique_ptr<Weapon>>& GetWeapons() const;

    void OnBaseCollision(bool isCollidedOnWall);

    void Hit(int _damage);

    void AddWeapons(std::vector<Weapon> wp);

    void SetWeapons(const std::vector<Weapon> wp);

    int GetCurrentWeaponIndex() const;

    const int GetHighestLevel() const { return _highestLevel; }

    void SetHighestLevel(int level) { if (level > _highestLevel) _highestLevel = level; }

    void HandleAnimationFinished() override;

    void ChangeState(const string &state) override;
	void DeadState();

	string GetAnimationToken() override;

	void ToggleCheats();

    void ReloadState();

    void ShootState();

    void IdleState();

    bool CanShoot();

	const std::string& GetSaveName() const { return _saveName; }

	void SetSaveName(const std::string value) { _saveName = value; }

	int GetPoints() const;
	void AddPoints(int value);
};


// ReSharper disable once CppInconsistentNaming
void to_json(nlohmann::json &j, const Player &value);

void from_json(const nlohmann::json &j, Player &value);

#endif //SHOOTER_PLAYER_H
