//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_MOVEABLEOBJECT_H
#define SHOOTER_MOVEABLEOBJECT_H


#include <string>
#include "Direction.h"

class MoveableObject {

private:
    SDL_Texture* _sprite;

    int xPos, yPos;

    void moveTop();

    void moveLeft();

    void moveRight();

    void moveBottom();

public:
    MoveableObject(const std::string &filePath, int xPos, int yPos);

    int getXPos() const;

    int getYPos() const;

    void move(Direction direction);

    void draw(float x, float y, double angle);
};


#endif //SHOOTER_MOVEABLEOBJECT_H
