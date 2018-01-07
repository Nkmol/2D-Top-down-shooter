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

    int damage;
public:

    Bullet(const string &filePath, Point coordinates, int damage);

    void update(float time) override;

    const int getDamage() const;
	void SetDamage(int damage);
	void onBaseCollision(MoveableObject * object);
	void onBaseCollision(bool isCollidedOnWall);
};


#endif //SHOOTER_BULLET_H
