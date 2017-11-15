#pragma once

class CollidableObject {
public:
	CollidableObject(const int x, const int y, const int width, const int height);
private:
	int x, y, width, height;
};