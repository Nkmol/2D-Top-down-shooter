#pragma once
#include "IHudComponent.h"
#include <string>

class TextComponent : public IHudComponent
{
	std::string _text;

public:
	TextComponent(std::string text, Point pos, int w, int h, float time = 0.0f, double angle = 0);

	void Update(float time) override;
	void Draw() override;
};