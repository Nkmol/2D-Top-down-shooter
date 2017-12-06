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

class MoveableObject : public GameObject {

private:
    SDL_Texture *_sprite;

    std::map<Point, int> directionAngles;

protected:
    bool visible;
    int angle, radius;
	float speed, distance;
    Point _destination;

public:
	MoveableObject(const std::string &filePath, const Point coordinates, const float speed);
	virtual ~MoveableObject();

    virtual void draw();

    virtual void update(float time);

    void SetAngle(int angle);

	void SetCoordinates(const Point& value);
    const Point &GetCoordinates() const;

    int getAngle() const;

    void stopMove();

    bool isVisible() const;

    const int getMidX(float destinationPosition) const;

    const int getMidY(float destinationPosition) const;

    void hide();
};


#endif //SHOOTER_MOVEABLEOBJECT_H
