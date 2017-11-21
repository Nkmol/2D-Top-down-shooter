#pragma once
class Button {
public:
	int getX1();
	int getY1();
	int getY2();
	int getX2();
	Button(int, int, int, int);
private:
	int x1;
	int x2;
	int y1;
	int y2;
	int width;
	int height;
	void setX2andY2(int, int, int, int);
};