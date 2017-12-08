#include "Button.h"

Button::Button(std::string &mediatoken, int x1, int y1, int width, int height) : GameObject(Point(x1, y1), width, height) {
	_x1Pos = x1;
	_y1Pos = y1;
	setX2andY2(x1, y1, width, height);

	SDL_Surface* surface = AssetManager::Instance().LoadSurface(mediatoken);
	if (!surface)
		cout << SDL_GetError() << endl;
	_sprite = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);

	SDL_FreeSurface(surface);
	if (this->_sprite == NULL)
	{
		printf(SDL_GetError());
	}
}

Button::Button() 
{

}

void Button::setX2andY2(int x1, int y1, int width, int height)
{
	_x2Pos = x1 + width;
	_y2Pos = y1 + height;
}

void Button::drawButton() {
	int w, h;
	SDL_QueryTexture(this->_sprite, nullptr, nullptr, &w, &h);

	SDL_Rect destinationRectangle = { static_cast<int>(_x1Pos), static_cast<int>(_y1Pos), w, h };
	RenderManager::Instance().DrawTexture(this->_sprite, nullptr, &destinationRectangle, 0);
}

int Button::getX1() {
	return this->_x1Pos; 
}

int Button::getY1() { 
	return this->_y1Pos; 
}

int Button::getY2() { 
	return this->_y2Pos; 
}

int Button::getX2() { 
	return this->_x2Pos; 
}

