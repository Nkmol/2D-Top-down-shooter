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

    std::map<Direction, int> directionAngles;

protected:
    bool visible;
    int angle;
    float speed;
    float xPos, yPos, distance, destinationXPos, destinationYPos;

public:
    MoveableObject(const std::string &filePath, float xPos, float yPos, float speed);

    ~MoveableObject();

    virtual void draw();

    virtual void update(float time);

    float getXPos() const;

    float getYPos() const;

    void setXPos(float xPos);

    void setYPos(float yPos);

    void setAngle(int angle);

    int getAngle() const;

    void stopMove();

    bool isVisible() const;

    void setDestinationXPos(float destinationXPos);

    void setDestinationYPos(float destinationYPos);

};


#endif //SHOOTER_MOVEABLEOBJECT_H
