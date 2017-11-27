//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H


#include "MoveableObject.h"
#include "Weapon.h"
#include "Point.h"

class Player : public MoveableObject {

    Weapon weapon;
public:
    Player(const std::string &filePath, int xPos, int yPos);

    void shoot();

    void addWeapon(Weapon &weapon);

    Weapon &getWeapon();

    void Move(const Point direction);

    void draw() override;

    void update(float time) override;
};


#endif //SHOOTER_PLAYER_H
