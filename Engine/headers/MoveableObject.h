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
#include <AssetManager.h>

enum classType {
    MOVEABLEOBJECT,
    BULLET,
    ENEMY,
    PLAYER
};

class MoveableObject : public GameObject {

private:
    std::map<Point, int> directionAngles;

protected:

    float speed, distance;
    Point _destination;
    classType _type;

    std::string _state;
    int frames;
    float currentAnimationTimer;
    float animationTimer = 0;
    int currentSprite = 0;

public:

    MoveableObject(const std::string &filePath, const Point coordinates, const float speed);

    virtual ~MoveableObject();

    virtual void draw();

    virtual void update(float time);

    void stopMove();

    const int getPredictionMidX(float destinationPosition) const;

    const int getMidX() const;

    const int getMidY() const;

    const int getPredictionMidY(float destinationPosition) const;

    classType getType();

    virtual void onBaseCollision(MoveableObject *object);

    virtual void onBaseCollision(bool isWall);

    virtual void onBaseCollision(GameObject object);

    virtual string GetAnimationToken();


    virtual void HandleAnimationFinished();

    virtual void ChangeState(const string &_state);


    const string &GetState() const;

    int NextSpriteIndex();

    bool IsAnimationFinished();

    bool IsReadyForAnimation() const;

    void ChangeSprite(const std::string &spriteToken);

    void DecreaseAnimationTimer(double by);

    void ResetAnimationTimer();

};


#endif //SHOOTER_MOVEABLEOBJECT_H
