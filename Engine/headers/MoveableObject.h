//
// Created by Mevlüt Özdemir on 09-11-17.
//

#ifndef SHOOTER_MOVEABLEOBJECT_H
#define SHOOTER_MOVEABLEOBJECT_H

#include "RenderManager.h"
#include <SDL_render.h>
#include <string>
#include "Point.h"
#include <AssetManager.h>
#include "GameObject.h"

enum classType
{
	MOVEABLEOBJECT,
	BULLET,
	ENEMY,
	PLAYER
};


class MoveableObject : public GameObject {

private:
    SDL_Texture *_sprite;

    std::map<Point, int> directionAngles;

protected:

    int angle, radius;
	float speed, distance;
    Point _destination;
	classType _type;

public:
    ~MoveableObject();

    MoveableObject(const std::string &filePath, const Point coordinates, const float speed);

    virtual void draw();

    virtual void update(float time);

    void SetAngle(int angle);

    int getAngle() const;

    void stopMove();

 

    const int getMidX() const;

    const int getMidY() const;

	const int getPredictionMidX(float destinationPosition) const;

	const int getPredictionMidY(float destinationPosition) const;

    void hide();

	classType getType();

	virtual void onBaseCollision(shared_ptr<MoveableObject> moveableObject);
	virtual void onCollision(bool isCollidedOnWall);
};


#endif //SHOOTER_MOVEABLEOBJECT_H
