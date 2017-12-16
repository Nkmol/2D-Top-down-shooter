#pragma once
#include "IHudComponent.h"
#include <string>

class TextComponent : public IHudComponent
{
	std::string _text;

public:
	TextComponent(std::string text, Point pos, int w, int h, double angle = 0);

	void Update(float time) override;
	void Draw() override;
	void ChangeText(const std::string text);
};