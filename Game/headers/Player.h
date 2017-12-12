//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H


#include "MoveableObject.h"
#include "Weapon.h"
#include "json.hpp"
#include "Bullet.h"

class PlayerState;

class Point;

class Player : public MoveableObject {

    std::vector<Weapon> weapons;
    int currentWeapon;

private:
    // don't need to delete, it's a reference to a weapon inside de weapons vector.
    int lifepoints;


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

    const vector<Weapon> &getWeapons() const;

    void addWeapons(std::vector<Weapon> wp);

    void SetWeapons(const std::vector<Weapon> wp);

    int getCurrentWeaponIndex() const;


    void SetState(const string &_state);

//    string getAnimationToken() override;
};

// ReSharper disable once CppInconsistentNaming
void to_json(nlohmann::json &j, const Player &value);

void from_json(const nlohmann::json &j, Player &value);

#endif //SHOOTER_PLAYER_H
