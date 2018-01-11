#pragma once
#include "UIElement.h"

class UIIcon : public UIElement
{
	int _opacity;
	std::string _token;

	void LoadTexture();
public:
	UIIcon(const std::string token, const Point& position);
	UIIcon(const std::string token, const Point& position, int opacity, float lifetime = 0);

	void Draw() override;

	const int GetOpacity() const { return _opacity; }
	void SetOpacity(int value);
};