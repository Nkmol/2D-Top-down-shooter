//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H


#include "MoveableObject.h"
#include "Weapon.h"

class Player : public MoveableObject {

private:
    Weapon weapon;

public:
    Player(const std::string &filePath, int xPos, int yPos);

    void shoot();

    void addWeapon(Weapon &weapon);

    Weapon& getWeapon();

    void updateWeapon(int time);

    void move(Direction direction);

    void moveTop();

    void moveRight();

    void moveBottom();

    void moveLeft();
};


#endif //SHOOTER_PLAYER_H
