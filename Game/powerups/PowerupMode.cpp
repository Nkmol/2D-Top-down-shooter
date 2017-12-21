//
// Created by Ahmad Rahimi on 12/21/17.
//

#include "PowerupMode.h"

void PowerupMode::update(float time, Player &player) {
    counter += time;
    if(counter < maxTime){
        if(!didPowerUp) {
            didPowerUp = true;
            powerupPlayer(player);
        }
    }else{
        removePowerup(player);
    }
}

PowerupMode::PowerupMode(float maxTime) : maxTime(maxTime) {

}

float PowerupMode::getCounter() const {
    return counter;
}

float PowerupMode::getMaxTime() const {
    return maxTime;
}

void PowerupMode::powerupPlayer(Player &player) {

}

void PowerupMode::removePowerup(Player &player) {

}
