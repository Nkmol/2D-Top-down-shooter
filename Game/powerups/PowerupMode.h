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
    void Update(float time, Player &player);
    virtual void PowerupPlayer(Player &player);
    virtual void RemovePowerup(Player &player);
    float GetCounter() const;
    float GetMaxTime() const;
};


#endif //SHOOTER_POWERUPMODE_H
