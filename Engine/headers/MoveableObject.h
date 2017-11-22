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

    float destinationYPos;

    int angle;

    std::map<Direction, int> directionAngles;

protected:
    bool visible;
    float yPos;
    float speed;
    float destinationXPos;
    float xPos;
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
