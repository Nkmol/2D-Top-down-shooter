#pragma once

#include <SDL_rect.h>
#include "Point.h"

class GameObject {
public:
	GameObject(Point coordinates, int width, int height);
	const int getMidX() const;
	const int getMidY() const;
	const int getRadius() const;
	int getWidth() const;
	int getHeight() const;
	int GetId() const;
	const Point &GetCoordinates() const;
	const SDL_Rect GetRect() const;
	void update(float time);
	void draw();

protected:
	int width, height;
	float radius, midX, midY;
	Point _coordinates;
private:
	int id;
	static int counter;

};