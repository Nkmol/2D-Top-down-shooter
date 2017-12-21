//
// Created by Ahmad Rahimi on 12/21/17.
//

#ifndef SHOOTER_POWERUPMODEFASTSHOT_H
#define SHOOTER_POWERUPMODEFASTSHOT_H


#include "PowerupMode.h"
class PowerupModeFastShot : public PowerupMode {
public:
    PowerupModeFastShot(float maxTime = 10);
    void powerupPlayer(Player &player);
    void removePowerup(Player &player);
};


#endif //SHOOTER_POWERUPMODEFASTSHOT_H
