//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H


#include "MoveableObject.h"

class Player : public MoveableObject {


public:
    Player(const std::string &filePath, int xPos, int yPos);
};


#endif //SHOOTER_PLAYER_H
