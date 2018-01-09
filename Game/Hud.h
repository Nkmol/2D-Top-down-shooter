#pragma once
#include <vector>
#include "../Engine/UIElement.h"

class Hud
{
	static Hud* _instance;
	std::vector<UIElement*> _components;

	Hud();
public:
	Hud(Hud const&) = delete;
	void operator=(Hud const&) = delete;

	static Hud& Instance();

	void Update(float time);
	void Draw();

	void AddComponent(UIElement* comp);
	void RemoveComponent(UIElement* comp);
};