//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_WEAPON_H
#define SHOOTER_WEAPON_H

#include "json.hpp"

class Point;
class Bullet;

class Weapon
{
protected:
	int damage;
	int maxBullets;
	int shooted = 0;
	std::string name;

public:
	Weapon(int damage, std::string name, int maxBullets);

	Bullet getBullet(int angle, Point coordinates, bool isCheatActive);

	bool hasBullets();

	int totalBullets() const;

	int getShooted() const;
	int getMaxBullets() const;
	void SetName(const std::string& v);
	void SetCurrentBullets(const int v);

	std::string getName() const;

	void Reload();

	bool CanReload() const;
};

void to_json(nlohmann::json& j, const Weapon& value);

void from_json(const nlohmann::json& j, Weapon& value);

#endif //SHOOTER_WEAPON_H
