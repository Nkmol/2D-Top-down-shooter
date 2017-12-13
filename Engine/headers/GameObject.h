#pragma once
#include <string>
#include <SDL_rect.h>
#include "Point.h"
#include "RenderManager.h"
#include <SDL_render.h>
#include <vector>

class GameObject {
public:
	GameObject(Point coordinates, int width, int height);
	GameObject(const std::string & spriteToken, const Point coordinates);
	const int getMidX() const;
	const int getMidY() const;
	int getWidth() const;
	int getHeight() const;
	void SetCoordinates(const Point & value);
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
	const int getRadius() const;
    virtual void update(float time);
	GameObject();
	void incrementId();
	void setNearbyObjects(std::vector<reference_wrapper<GameObject>> &nearbyObjects);

protected:
	int width, height, angle;
	float radius, midX, midY;
	Point _coordinates;
	bool visible;
	SDL_Texture *_sprite;
private:
	std::vector<reference_wrapper<GameObject>> nearbyObjects;
public:
	const std::vector<reference_wrapper<GameObject>> &getNearbyObjects() const;

private:
	int id;
	int teamId = -1;
	static int counter;


};