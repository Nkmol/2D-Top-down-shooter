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

class Point;

class Player : public MoveableObject {

    vector<Weapon> weapons;
    unsigned currentWeapon;

private:
    int lifepoints;
    int _highestLevel = 1;
	bool isCheatActive;

public:
    Player(const std::string &filePath, float x, float y);

    Player(const std::string &filePath, Point coordinates, int lp = 100);
	~Player();

    Bullet shoot();

    void Move(const Point direction);

    void update(float time) override;

    const int getLifepoints() const;

    const int changeLifepoints(const int lp);

    Weapon *getWeapon();

    void changeWeapon(unsigned index);

	bool GetIsCheatActive();

    const vector<Weapon> &getWeapons() const;

    void onBaseCollision(bool isCollidedOnWall);

    void Hit(int damage);

    void addWeapons(std::vector<Weapon> wp);

    void SetWeapons(const std::vector<Weapon> wp);

    int getCurrentWeaponIndex() const;

    const int GetHighestLevel() const { return _highestLevel; }

    void SetHighestLevel(int level) { if (level > _highestLevel) _highestLevel = level; }

    void HandleAnimationFinished() override;

    void ChangeState(const string &_state) override;

    string GetAnimationToken() override;

	void ToggleCheats();

    void ReloadState();

    void ShootState();

    void IdleState();

    bool CanShoot();
};


// ReSharper disable once CppInconsistentNaming
void to_json(nlohmann::json &j, const Player &value);

void from_json(const nlohmann::json &j, Player &value);

#endif //SHOOTER_PLAYER_H
