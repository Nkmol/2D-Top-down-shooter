#pragma once
#include "GameObject.h"

class UIText
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
	Texture _texture{};
	AssetManager::Font _font;

	SDL_Rect _rect{};
	RGBA _colour{};
	std::string _text;
	Point _coordinates;
	int _angle{};

	void LoadSurface();
public:
	UIText();
	UIText(const std::string& text, unsigned fontSize);
	UIText(const std::string& text, unsigned fontSize, const Point& position);
	UIText(const std::string&  text, unsigned fontSize, const Point& position, const RGBA& colour);

	void Draw();
	void Center();
	void ChangeText(const std::string& text);
};

