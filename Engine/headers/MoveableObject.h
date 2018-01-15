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
    std::map<Point, int> _directionAngles;

protected:

    float speed, distance;
    Point destination;
    classType type;

    std::string state;
    int frames;
    float currentAnimationTimer;
    float animationTimer = 0;
    int currentSprite = 0;

public:

    MoveableObject(const std::string &filePath, const Point coordinates, const float speed);

    virtual ~MoveableObject();

    virtual void Update(float time);

    void StopMove();

    const int GetPredictionMidX(float destinationPosition) const;

    const int GetMidX() const;

    const int GetMidY() const;

    const int GetPredictionMidY(float destinationPosition) const;

    classType GetType();

    virtual void OnBaseCollision(MoveableObject *object);

    virtual void OnBaseCollision(bool isWall);

    virtual void OnBaseCollision(GameObject object);

    virtual string GetAnimationToken();


    virtual void HandleAnimationFinished();

    virtual void ChangeState(const string &state);


    const string &GetState() const;

    int NextSpriteIndex();

    bool IsAnimationFinished();

    bool IsReadyForAnimation() const;

    void ChangeSprite(const std::string &_spriteToken);

    void DecreaseAnimationTimer(double by);

    void ResetAnimationTimer();

    void ChangeTexture(Texture &texture);
};


#endif //SHOOTER_MOVEABLEOBJECT_H
