//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_PLAYER_H
#define SHOOTER_PLAYER_H


#include "MoveableObject.h"
#include "Weapon.h"

class Player : public MoveableObject {

    Weapon weapon;
    float WALKING_SPEED = 0.4f;
	int lifepoints;

public:
    Player(const std::string &filePath, int xPos, int yPos, int lp = 100);

    void shoot();

    void addWeapon(Weapon &weapon);

    Weapon &getWeapon();

    void move(Direction direction);

    void moveTop();

    void moveRight();

    void moveBottom();

    void moveLeft();

    void draw() override;

    void update(float time) override;

	const int getLifepoints() const;

	const int changeLifepoints(const int lp);
	
};


#endif //SHOOTER_PLAYER_H
