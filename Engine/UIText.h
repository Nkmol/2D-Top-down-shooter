#pragma once
#include "GameObject.h"
#include "CustomDeleter.h"

class UIText :
	public GameObject
{
public:
	struct RGBA
	{
		Uint8 R, G, B, A;

		// Implicit from struct to SDL_Color
		operator SDL_Color() const {
			// Use Implicit constructor of SDL_Color
			return { R, G, B, A };
		}
	};
private:
	unique_ptr<SDL_Surface, CustomDeleter> _surface;
	SDL_Rect _rect{};
	RGBA _colour;
	std::string _text;
public:
	UIText(const std::string& text, const unsigned fontSize);
	UIText(const std::string& text, unsigned fontSize, const Point& position);
	UIText(std::string  text, unsigned fontSize, const Point& position, const RGBA& colour);
	void Draw();
	void Center();
	~UIText();
};

