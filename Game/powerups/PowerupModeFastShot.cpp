//
// Created by Ahmad Rahimi on 12/21/17.
//

#include "PowerupModeFastShot.h"
#include "Player.h"
PowerupModeFastShot::PowerupModeFastShot(float maxTime) : PowerupMode(maxTime) {

}

void PowerupModeFastShot::powerupPlayer(Player &player) {
    if(player.getWeapon()->getStandardFireRate() == player.getWeapon()->getFireRate()) {
        player.getWeapon()->setFireRate(player.getWeapon()->getFireRate() / 5);
    }
}

void PowerupModeFastShot::removePowerup(Player &player) {
    player.getWeapon()->setFireRate(player.getWeapon()->getStandardFireRate());
}
