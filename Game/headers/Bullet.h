//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_BULLET_H
#define SHOOTER_BULLET_H


#include <MoveableObject.h>

class Bullet : public MoveableObject {

private:
    float BULLET_SPEED = 0.8f;

public:
    Bullet(const string &filePath, float xPos, float yPos);

    Bullet(const string &filePath, float xPos, float yPos, float speed, const Bullet &other);

    void makeVisible();

    void makeInvisible();

    void update(float time);
};


#endif //SHOOTER_BULLET_H
