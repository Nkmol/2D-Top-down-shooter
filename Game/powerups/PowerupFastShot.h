//
// Created by Ahmad Rahimi on 12/20/17.
//

#ifndef SHOOTER_FASTSHOOT_H
#define SHOOTER_FASTSHOOT_H


#include "DropableObject.h"

class PowerupFastShot : public DropableObject {
public:
    PowerupFastShot(const Point &coordinates,const string &spriteToken = "powerup_fastshot");

    void ActivateDropable(Player &player) override;
};


#endif //SHOOTER_FASTSHOOT_H
