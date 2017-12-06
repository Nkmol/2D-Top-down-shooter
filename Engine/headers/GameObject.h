#pragma once
#include <string>

#include <SDL_rect.h>
#include "Point.h"
#include "PhysicsManager.h"

class GameObject {
public:
	GameObject(Point coordinates, int width, int height);
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
	int GetTeamId() const;
	void SetTeamId(int teamId);
	const int getRadius() const ;
	bool isVisible() const;
protected:
	bool visible;
	GameObject();
	int width, height;
	float radius, midX, midY;
	Point _coordinates;
private:
	int id;
	int teamId = -1;
	static int counter;

};