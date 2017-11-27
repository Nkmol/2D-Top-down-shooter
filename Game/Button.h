#pragma once
class Button {
public:
	Button();
	~Button();
	int getX1();
	int getY1();
	int getY2();
	int getX2();
	Button::Button(int, int, int, int);
private:
	int x1Pos;
	int x2Pos;
	int y1Pos;
	int y2Pos;
	int width;
	int height;
	void setX2andY2(int, int, int, int);
};