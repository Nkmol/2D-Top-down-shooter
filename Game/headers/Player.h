//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H


#include "MoveableObject.h"
#include "Weapon.h"
#include "Point.h"
#include <Weapon.h>

class Player : public MoveableObject {

    std::vector<Weapon> weapons;
    Weapon *weapon;

private:
    // don't need to delete, it's a reference to a weapon inside de weapons vector.
    int lifepoints;

public:
    Player(const std::string &filePath, float x, float y);

    Player(const std::string &filePath, Point coordinates, int lp = 100);

    Bullet shoot();

    void Move(const Point direction);

    void update(float time) override;

    const int getLifepoints() const;

    const int changeLifepoints(const int lp);

    void changeWeapon(int index);

    Weapon *getWeapon() const;

    void addWeapons(std::vector<Weapon> wp);

};


#endif //SHOOTER_PLAYER_H
