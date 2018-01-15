//
// Created by Ahmad Rahimi on 12/20/17.
//

#include <Helper.h>
#include "DropableObject.h"

DropableObject::DropableObject(const string &spriteToken, const Point &coordinates) : GameObject(spriteToken,
                                                                                                 coordinates) {}

void DropableObject::ActivateDropable(Player &player) {
    this->Hide();
}

void DropableObject::CheckForCollision(Player &player) {
    if(this->IsVisible()){
        Point pCoordinates = player.GetCoordinates();
        Point pOrigin = {(pCoordinates.x + (player.GetWidth()/2)), (pCoordinates.y + (player.GetHeight()/2))};
        Point origin = {(_coordinates.x + (GetWidth()/2)), (_coordinates.y + (GetHeight()/2))};
        float distance = int(abs(hypot(pOrigin.x - origin.x, pOrigin.y - origin.y)));
        if(distance < 32){
            ActivateDropable(player);
        }
    }
}
