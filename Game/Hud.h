#pragma once
#include <vector>

#include "IHudComponent.h"
#include "../Engine/UIText.h"

class Hud
{
	static Hud* _instance;
	std::vector<UIText*> _components;

	Hud();
public:
	Hud(Hud const&) = delete;
	void operator=(Hud const&) = delete;

	static Hud& Instance();

	void Update(float time);
	void Draw();

	void AddComponent(UIText* comp);
	void RemoveComponent(UIText* comp);
};