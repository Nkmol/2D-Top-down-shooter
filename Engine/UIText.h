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
	// TODO Smart
	SDL_Surface* _surface;
	TTF_Font* _font;

	SDL_Rect _rect{};
	RGBA _colour;
	std::string _text;
	void LoadSurface();
public:
	UIText();
	UIText(const std::string& text, const unsigned fontSize);
	UIText(const std::string& text, unsigned fontSize, const Point& position);
	UIText(const std::string&  text, unsigned fontSize, const Point& position, const RGBA& colour);
	~UIText();
	void Draw();
	void Center();
	void ChangeText(const std::string& text);
	UIText& operator=(const UIText& uiText) = default;
};

