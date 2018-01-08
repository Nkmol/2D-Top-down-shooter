#pragma once
#include "IHudComponent.h"
#include <string>

class NumberComponent : public IHudComponent
{
	int* _number;

public:
	NumberComponent(int* number, Point pos, int w, int h, float time = 0.0f, double angle = 0);

	void Update(float time) override;
	void Draw() override;
};