//
// Created by Ahmad Rahimi on 12/20/17.
//

#ifndef SHOOTER_DROPABLEOBJECT_H
#define SHOOTER_DROPABLEOBJECT_H


#include <GameObject.h>
#include <Player.h>

class DropableObject : public GameObject {
public:
    DropableObject(const string &spriteToken, const Point &coordinates);
    virtual void ActivateDropable(Player &player);
    void CheckForCollision(Player &player);
};


#endif //SHOOTER_DROPABLEOBJECT_H
