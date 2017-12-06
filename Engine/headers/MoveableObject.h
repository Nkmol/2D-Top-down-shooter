//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_MOVEABLEOBJECT_H
#define SHOOTER_MOVEABLEOBJECT_H

#include "RenderManager.h"
#include <SDL_render.h>
#include <string>
#include "PhysicsManager.h"
#include "GameObject.h"
#include "Point.h"

class MoveableObject : public GameObject {

private:
    std::map<Point, int> directionAngles;
	string token;
protected:

	float speed, distance;
    Point _destination;

public:
    ~MoveableObject();

    MoveableObject(const std::string &filePath, const Point coordinates, const float speed);

    virtual void draw();

    virtual void update(float time);

    void stopMove();

    const int getMidX(float destinationPosition) const;

    const int getMidY(float destinationPosition) const;

};


#endif //SHOOTER_MOVEABLEOBJECT_H
