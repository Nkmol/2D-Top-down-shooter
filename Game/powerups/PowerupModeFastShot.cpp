//
// Created by Ahmad Rahimi on 12/21/17.
//

#include "PowerupModeFastShot.h"
#include "Player.h"
PowerupModeFastShot::PowerupModeFastShot(float maxTime) : PowerupMode(maxTime) {

}

void PowerupModeFastShot::PowerupPlayer(Player &player) {
    if(player.GetWeapon()->getStandardFireRate() == player.GetWeapon()->getFireRate()) {
        player.GetWeapon()->setFireRate(player.GetWeapon()->getFireRate() / 2);
    }
}

void PowerupModeFastShot::RemovePowerup(Player &player) {
    player.GetWeapon()->setFireRate(player.GetWeapon()->getStandardFireRate());
}
