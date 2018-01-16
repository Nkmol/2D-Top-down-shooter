//
// Created by Ahmad Rahimi on 12/21/17.
//

#include "PowerupModeFastShot.h"
#include "Player.h"
PowerupModeFastShot::PowerupModeFastShot(float maxTime) : PowerupMode(maxTime) {

}

void PowerupModeFastShot::powerupPlayer(Player &player) {
    if(player.GetWeapon()->GetStandardFireRate() == player.GetWeapon()->GetFireRate()) {
        player.GetWeapon()->SetFireRate(player.GetWeapon()->GetFireRate() / 2);
    }
}

void PowerupModeFastShot::removePowerup(Player &player) {
    player.GetWeapon()->SetFireRate(player.GetWeapon()->GetStandardFireRate());
}
