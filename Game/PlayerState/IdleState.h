//
// Created by Mevlüt Özdemir on 08-12-17.
//

#ifndef SHOOTER_IDLESTATE_H
#define SHOOTER_IDLESTATE_H

#include "PlayerState.h"

class IdleState : public PlayerState {

public:
    using PlayerState::PlayerState;

    ~IdleState();

    void Update() override;
};


#endif //SHOOTER_IDLESTATE_H
