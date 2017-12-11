//
// Created by Mevlüt Özdemir on 08-12-17.
//

#ifndef SHOOTER_PLAYERSTATE_H
#define SHOOTER_PLAYERSTATE_H


#include "Player.h"

class PlayerState {

    Player &_player;
public:
    PlayerState(Player &player) : _player{player} {}

    virtual ~PlayerState() = default;

    virtual void Update() {}
};


#endif //SHOOTER_PLAYERSTATE_H
