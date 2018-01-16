#pragma once
#include "UIElement.h"

class UIText : public UIElement
{
public:

private:
	Font _font;
	RGBA _colour{};
	std::string _text;
	void LoadSurface();
public:
	UIText();
	UIText(const std::string& text, unsigned fontSize, float lifetime = 0);
	UIText(const std::string& text, unsigned fontSize, const Point& position, float lifetime = 0);
	UIText(const std::string& text, unsigned fontSize, const Point& position, const RGBA& colour, float lifetime = 0);

	void Draw() override;
	void ChangeText(const std::string& text);
};

