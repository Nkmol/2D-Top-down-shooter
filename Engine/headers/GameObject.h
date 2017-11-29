#pragma once


class GameObject {
public:
	GameObject(const float x, const float y, const int width, const int height);
	const int getMidX() const;
	const int getMidY() const;
	const int getRadius() const;
	int getWidth() const;
	int getHeight() const;

private:
	int width, height;
	float x, y, radius, midX, midY;
	
};