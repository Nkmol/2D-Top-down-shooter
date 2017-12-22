//
// Created by Ahmad Rahimi on 12/20/17.
//

#ifndef SHOOTER_POWERUPHP_H
#define SHOOTER_POWERUPHP_H


#include "DropableObject.h"

class PowerupHP : public DropableObject {
private:
    int increaseBy = 25;
public:
    PowerupHP(const Point &coordinates,const string &spriteToken = "powerup_hp");
    void ActivateDropable(Player &player);
};


#endif //SHOOTER_POWERUPHP_H
