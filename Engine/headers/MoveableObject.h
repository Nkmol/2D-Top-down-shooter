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

protected:
    std::string token;
    float speed, distance;
    std::string _state;
    int _frames;
    Point _destination;
    float animationTimer;
    int currentSprite = 0;

public:

    MoveableObject(const std::string &filePath, const Point coordinates, const float speed);

    virtual ~MoveableObject();

    virtual void draw();

    virtual void update(float time);

    void SetAngle(int angle);

    void SetCoordinates(const Point &value);

    const Point &GetCoordinates() const;

    int getAngle() const;

    void stopMove();

    const int getMidX(float destinationPosition) const;

    const int getMidY(float destinationPosition) const;




    // all for animation:
    // todo: new inherticance from Animation ??
    virtual string getAnimationToken();

    const string &GetState() const;

    virtual void HandleAnimationFinished();

    void SetFrames(int _frames);

    void setAnimationTimer(float animationTimer);

    float getAnimationTimer() const;

    virtual void SetState(const string &_state);

    bool readyForAnimation() const;

    void changeSprite(const std::string &spriteToken);

    void setCurrentSpriteIndex(int index);

    int getNextSpriteIndex();

    bool AnimationFinished();

    void DecreaseAnimationTimer(float by);
};


#endif //SHOOTER_MOVEABLEOBJECT_H
