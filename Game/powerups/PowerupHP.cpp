//
// Created by Ahmad Rahimi on 12/20/17.
//

#include "PowerupHP.h"

PowerupHP::PowerupHP(const Point &coordinates, const string &spriteToken) : DropableObject(spriteToken, coordinates) {
}

void PowerupHP::ActivateDropable(Player &player) {
    player.changeLifepoints(increaseBy);
    DropableObject::ActivateDropable(player);
}
