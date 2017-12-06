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

enum classType
{
	MOVEABLEOBJECT,
	BULLET,
	ENEMY,
	PLAYER
};

class MoveableObject {

private:
    SDL_Texture *_sprite;

    std::map<Point, int> directionAngles;

protected:
    bool visible;
    int angle, radius, midX, midY, width, height;
	float speed;
    float distance;
    Point _destination;
    Point _coordinates;
	classType _type;

public:
    ~MoveableObject();

    MoveableObject(const std::string &filePath, const Point coordinates, const float speed);

    virtual void draw();

    virtual void update(float time);

    void SetAngle(int angle);

    const Point &GetCoordinates() const;

    int getAngle() const;

    void stopMove();

    bool isVisible() const;

    const int getMidX() const;

    const int getMidY() const;

	const int getPredictionMidX(float destinationPosition) const;

	const int getPredictionMidY(float destinationPosition) const;

    const int getRadius() const;

	int getWidth() const;

	int getHeight() const;

    void hide();

	classType getType();

	virtual void onBaseCollision(shared_ptr<MoveableObject> moveableObject);
	virtual void onCollision(bool isCollidedOnWall);
};


#endif //SHOOTER_MOVEABLEOBJECT_H
