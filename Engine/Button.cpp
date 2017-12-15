#include "RenderManager.h"
#include "AssetManager.h"
#include "Button.h"
Button::Button(const std::string mediatoken, int x1, int y1, int width, int height) : GameObject(Point(x1, y1), width, height) {
	x1Pos = x1;
	y1Pos = y1;
	setX2andY2(x1, y1, width, height);
	SDL_Surface* surface = AssetManager::Instance().LoadSurface(mediatoken);
	if (!surface)
		cout << SDL_GetError() << endl;
	_sprite = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);

	//SDL_FreeSurface(surface);
	if (this->_sprite == NULL)
	{
		printf(SDL_GetError());
	}
}

Button::Button() {}

void Button::setX2andY2(int x1, int y1, int width, int height)
{
	x2Pos = x1 + width;
	y2Pos = y1 + height;
}

void Button::drawButton() {
	int w, h;
	SDL_QueryTexture(this->_sprite, nullptr, nullptr, &w, &h);

	SDL_Rect destinationRectangle = { static_cast<int>(x1Pos), static_cast<int>(y1Pos), w, h };
	RenderManager::Instance().DrawTexture(this->_sprite, nullptr, &destinationRectangle, 0);
}

int Button::getX1() { return this->x1Pos; }
int Button::getY1() { return this->y1Pos; }
int Button::getY2() { return this->y2Pos; }
int Button::getX2() { return this->x2Pos; }

