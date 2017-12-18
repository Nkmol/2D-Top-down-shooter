#pragma once
#include <string>
#include "GameObject.h"


class Button : public GameObject {
public:
	Button(const std::string mediatoken, int x1, int y1, int width, int height);
	Button();
	void drawButton();
	int getX1();
	int getY1();
	int getY2();
	int getX2();
private:
	int x1Pos;
	int x2Pos;
	int y1Pos;
	int y2Pos;
	int width;
	int height;
	SDL_Texture* _sprite;
	void setX2andY2(int, int, int, int);
};
