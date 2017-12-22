//
// Created by Ahmad Rahimi on 12/20/17.
//

#include "PowerupFastShot.h"
#include "PowerupModeFastShot.h"

PowerupFastShot::PowerupFastShot(const Point &coordinates, const string &spriteToken) : DropableObject(spriteToken, coordinates) {
}

void PowerupFastShot::ActivateDropable(Player &player) {
    player.powerupmodes.emplace_back(make_unique<PowerupModeFastShot>(PowerupModeFastShot()));
    DropableObject::ActivateDropable(player);
}