//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_MOVEABLEOBJECT_H
#define SHOOTER_MOVEABLEOBJECT_H

#include "RenderManager.h"
#include <SDL_render.h>
#include <string>
#include "PhysicsManager.h"
#include "Point.h"

class MoveableObject {

private:
    SDL_Texture *_sprite;

    std::map<Point, int> directionAngles;

protected:
    bool visible;
    int angle, radius, midX, midY, width, height;
    float speed;
    float xPos, yPos, distance;
	Point _destination;

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

	const int getMidX(float destinationPosition) const;

	const int getMidY(float destinationPosition) const;

	const int getRadius() const;
};


#endif //SHOOTER_MOVEABLEOBJECT_H
