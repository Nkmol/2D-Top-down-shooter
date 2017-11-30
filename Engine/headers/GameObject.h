#pragma once
#include <string>


class GameObject {
public:
	GameObject(const std::string mediatoken, const float x, const float y, const int width, const int height);
	const int getMidX() const;
	const int getMidY() const;
	const int getRadius() const ;
	GameObject();
private:
	int width, height;
	float x, y, radius, midX, midY;
	
};