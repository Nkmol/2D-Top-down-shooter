//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_BULLET_H
#define SHOOTER_BULLET_H


#include <MoveableObject.h>
#include "PhysicsManager.h"

class Bullet : public MoveableObject {

private:
    float BULLET_SPEED = 0.8f;

    int _damage;
public:

    int tempX = 0;
    int tempY = 0;

    Bullet(const string &filePath, Point coordinates, int _damage);

    void Update(float time) override;

    const int GetDamage() const;

    void SetDamage(int _damage);

    void OnBaseCollision(MoveableObject *object);

    void OnBaseCollision(bool isCollidedOnWall);

};


#endif //SHOOTER_BULLET_H
