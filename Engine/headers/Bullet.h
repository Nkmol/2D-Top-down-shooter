//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_BULLET_H
#define SHOOTER_BULLET_H


#include <MoveableObject.h>

class Bullet : public MoveableObject {

private:


public:
    Bullet(const string &filePath, float xPos, float yPos);

    void makeVisible();

    void makeInvisible();
};


#endif //SHOOTER_BULLET_H
