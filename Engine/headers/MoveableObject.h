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

    int xPos, yPos, speed, angle;

    std::map<Direction, int> directionAngles;

    void moveTop();

    void moveLeft();

    void moveRight();

    void moveBottom();

    void setAngle(Direction direction);

public:

    MoveableObject(const std::string &filePath, int xPos, int yPos);

    void move(Direction direction);

    void draw();

};


#endif //SHOOTER_MOVEABLEOBJECT_H
