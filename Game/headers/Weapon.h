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
    int damage;
    std::string name;
    int shooted = 0;
    int maxBullets;
    float fireRate;
    float standardFireRate;
    float lastShot;

public:
    Weapon(int damage, std::string name, int maxBullets, float fireRate);

    bool hasBullets();

    Bullet getBullet(int angle, Point coordinates);

    int totalBullets() const;

    int getShot() const;

    int getMaxBullets() const;

    void SetName(const std::string &v);

    void SetCurrentBullets(const int v);

    std::string getName() const;

    void Reload();

    bool CanReload() const;

    bool CanShoot() const;

    void UpdateFireRate(float time);

    void ResetLastShot();

    void setFireRate(float fireRate);

    float getFireRate() const;

    float getStandardFireRate() const;

};

void to_json(nlohmann::json &j, const Weapon &value);

void from_json(const nlohmann::json &j, Weapon &value);

#endif //SHOOTER_WEAPON_H
