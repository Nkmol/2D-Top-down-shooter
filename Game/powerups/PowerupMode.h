//
// Created by Ahmad Rahimi on 12/21/17.
//

#ifndef SHOOTER_POWERUPMODE_H
#define SHOOTER_POWERUPMODE_H

class Player;
class PowerupMode {
protected:
    float counter = 0;
    float maxTime;
    bool didPowerUp = false;

public:
    PowerupMode(float maxTime);
    void update(float time, Player &player);
    virtual void powerupPlayer(Player &player);
    virtual void removePowerup(Player &player);
    float getCounter() const;
    float getMaxTime() const;
};


#endif //SHOOTER_POWERUPMODE_H
