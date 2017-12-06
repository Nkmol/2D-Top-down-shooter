#pragma once
#include <string>
#include <SDL_rect.h>
#include "Point.h"
#include "RenderManager.h"
#include <SDL_render.h>

class GameObject {
public:
	GameObject(Point coordinates, int width, int height);
	GameObject(const std::string & spriteToken, const Point coordinates);

	const int getMidX() const;
	const int getMidY() const;
	int getWidth() const;
	int getHeight() const;
	int GetId() const;
	const Point &GetCoordinates() const;
	const SDL_Rect GetRect() const;
	void draw();
	int GetTeamId() const;
	int getAngle() const;
	void SetAngle(const int angle);
	void hide();
	bool isVisible() const;
	void SetTeamId(int teamId);
	const int getRadius() const ;
protected:
	bool visible;
	GameObject();
	int width, height, angle;
	float radius, midX, midY;
	Point _coordinates;
	SDL_Texture *_sprite;
private:

	int id;
	int teamId = -1;
	static int counter;


};