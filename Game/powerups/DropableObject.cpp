//
// Created by Ahmad Rahimi on 12/20/17.
//

#include <Helper.h>
#include "DropableObject.h"

DropableObject::DropableObject(const string &spriteToken, const Point &coordinates) : GameObject(spriteToken,
                                                                                                 coordinates) {}

void DropableObject::ActivateDropable(Player &player) {
    this->hide();
}

void DropableObject::checkForCollision(Player &player) {
    if(this->visible){
        Point pCoordinates = player.GetCoordinates();
        Point pOrigin = {(pCoordinates.x + (player.getWidth()/2)), (pCoordinates.y + (player.getHeight()/2))};
        Point origin = {(_coordinates.x + (getWidth()/2)), (_coordinates.y + (getHeight()/2))};
        float distance = int(abs(hypot(pOrigin.x - origin.x, pOrigin.y - origin.y)));
        if(distance < 32){
            ActivateDropable(player);
        }
    }
}
