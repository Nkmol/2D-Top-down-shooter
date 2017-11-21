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

private:
    SDL_Texture *_sprite;

    float xPos, yPos, distance, destinationXPos, destinationYPos;

    int angle;

    std::map<Direction, int> directionAngles;

    void moveTop();

    void moveLeft();

    void moveRight();

    void moveBottom();

protected:
    bool visible;

public:

    MoveableObject(const std::string &filePath, float xPos, float yPos);

    ~MoveableObject();

    float getXPos() const;

    float getYPos() const;

    void setXPos(float xPos);

    void setYPos(float yPos);

    void move(Direction direction);

    void draw();

    void setAngle(int angle);

    int getAngle() const;

    void update(float time);

    void stopMove();

    bool isVisible() const;

    void setDestinationXPos(float destinationXPos);

    void setDestinationYPos(float destinationYPos);

    float getDestinationXPos() const;

    float getDestinationYPos() const;
};


#endif //SHOOTER_MOVEABLEOBJECT_H
