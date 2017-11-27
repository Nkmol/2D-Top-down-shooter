//
// Created by Mevlüt Özdemir on 15-11-17.
//

#ifndef SHOOTER_BULLET_H
#define SHOOTER_BULLET_H


#include <MoveableObject.h>

class Bullet : public MoveableObject {

private:
    float BULLET_SPEED = 0.8f;
	int damage;
public:
    Bullet(const string &filePath, float xPos, float yPos, int damage);

    Bullet(const string &filePath, float xPos, float yPos, float speed, const Bullet &other, int damage);

    void makeVisible();

    void makeInvisible();

    void update(float time);

	const int getDamage() const;
};


#endif //SHOOTER_BULLET_H
