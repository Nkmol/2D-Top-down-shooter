//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_MOVEABLEOBJECT_H
#define SHOOTER_MOVEABLEOBJECT_H

#include "Direction.h"
#include "RenderManager.h"
#include <SDL_render.h>
#include <string>
#include "Direction.h"

class MoveableObject {

    SDL_Texture *_sprite;

    std::map<Direction, int> directionAngles;

    void moveTop();

    void moveLeft();

    void moveRight();

    void moveBottom();

protected:
    int angle;

    float xPos, yPos, distance, destinationXPos, destinationYPos;

public:
    MoveableObject(const std::string &filePath, float xPos, float yPos);

    float getXPos() const;

    float getYPos() const;

    void move(Direction direction);

    void draw();

    void setAngle(int angle);

    void update(float time);

    void stopMove();
};


#endif //SHOOTER_MOVEABLEOBJECT_H
