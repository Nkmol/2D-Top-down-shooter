#pragma once

#include <string>

#include <SDL_rect.h>
#include "Point.h"

class GameObject {

private:
    int damage;
    int id;
    int teamId = -1;
    static int counter;
    std::string name;

protected:
    GameObject();

    int width, height;
    float radius, midX, midY;
    Point _coordinates;

public:
    GameObject(std::string name, Point coordinates, int width, int height);

    GameObject(std::string name, Point coordinates, int width, int height, int damage);

    GameObject(const std::string mediatoken, const float x, const float y, const int width, const int height);

    const int getMidX() const;

    const int getMidY() const;

    int getWidth() const;

    int getHeight() const;

    int GetId() const;

    const Point &GetCoordinates() const;

    const SDL_Rect GetRect() const;

    void update(float time);

    void draw();

    virtual void onCollision(GameObject object);

    int GetTeamId() const;

    void SetTeamId(int teamId);

    const int getRadius() const;

    int getDamage() const;

    std::string GetName() const;

};