#pragma once
#include <string>
#include "SDL.h"
#include "GameObject.h"
class Button : public GameObject {
public:
	Button(std::string &mediatoken, int x1, int y1, int width, int height);
	Button();
	void drawButton();
	int getX1(), getY1(), getY2(), getX2();
private:
	int _x1Pos, _x2Pos, _y1Pos, _y2Pos;
	SDL_Texture* _sprite;
	void setX2andY2(int, int, int, int);
};
