//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H


#include "../../Engine/headers/MoveableObject.h"

class Player : public MoveableObject {


public:
    Player(int xPos, int yPos);
};


#endif //SHOOTER_PLAYER_H
