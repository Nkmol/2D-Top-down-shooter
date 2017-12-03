//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_WEAPON_H
#define SHOOTER_WEAPON_H


#include <iostream>
#include "Bullet.h"
#include <vector>
#include <memory>

#include "json.hpp"
using json = nlohmann::json;

class Weapon {

protected:
    int damage;
    int maxBullets;
    int shooted = 0;
    std::string name;

public:
	Weapon();
    Weapon(int damage, std::string name, int maxBullets);

    bool hasBullets();

    Bullet getBullet(int angle, Point coordinates);

    int totalBullets() const;

    int getShooted() const;
	int getMaxBullets() const;
	void SetName(const string& v);
	void SetCurrentBullets(const int v);

	std::string getName() const;
};

void to_json(json& j, const Weapon& value);

void from_json(const json& j, Weapon& value);

#endif //SHOOTER_WEAPON_H
