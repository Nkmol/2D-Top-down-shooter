#include <string>
#include <SDL_system.h>
#include "RenderManager.h"
//
// Created by Ahmad Rahimi on 11/9/17.
//
class Graphics;

class MoveableObject{
public:
    MoveableObject();
    MoveableObject(const std::string &filePath, float posX, float posY, int partnumber);
    virtual ~MoveableObject();
    virtual void update();
    void draw(float x, float y, double angle);
    SDL_Texture* _sprite;
    int _partnumber;
private:;
    float _x, _y;
};