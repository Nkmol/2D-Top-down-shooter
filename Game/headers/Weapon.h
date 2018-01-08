//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_WEAPON_H
#define SHOOTER_WEAPON_H

#include "json.hpp"

class Point;

class Bullet;

class Weapon {

protected:
    int _damage;
    std::string name;
    int shooted = 0;
    int maxBullets;
    float fireRate;
    float lastShot;
	std::string type;

public:
    Weapon(int _damage, std::string name, int maxBullets, float fireRate);

    bool HasBullets();

    int TotalBullets() const;

    int GetShot() const;

    int GetMaxBullets() const;

    void SetName(const std::string &v);

	Bullet GetBullet(int angle, Point coordinates, bool &isCheatActive);

    void SetCurrentBullets(const int v);

    std::string GetName() const;

    void Reload();

    bool CanReload() const;

    bool CanShoot() const;

    void UpdateFireRate(float time);

    void ResetLastShot();

	const std::string GetType() const;
};

void to_json(nlohmann::json &j, const Weapon &value);

void from_json(const nlohmann::json &j, Weapon &value);

#endif //SHOOTER_WEAPON_H
