//
// Created by Ahmad Rahimi on 12/21/17.
//

#include "PowerupMode.h"

void PowerupMode::Update(float time, Player &player) {
    counter += time;
    if(counter < maxTime){
        if(!didPowerUp) {
            didPowerUp = true;
            PowerupPlayer(player);
        }
    }else{
        RemovePowerup(player);
    }
}

PowerupMode::PowerupMode(float maxTime) : maxTime(maxTime) {

}

float PowerupMode::GetCounter() const {
    return counter;
}

float PowerupMode::GetMaxTime() const {
    return maxTime;
}

void PowerupMode::PowerupPlayer(Player &player) {

}

void PowerupMode::RemovePowerup(Player &player) {

}
