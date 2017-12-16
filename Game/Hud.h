#pragma once
#include <vector>

#include "IHudComponent.h"

class Hud
{
	static Hud* _instance;
	std::vector<IHudComponent*> _components;

	Hud();
public:
	Hud(Hud const&) = delete;
	void operator=(Hud const&) = delete;

	static Hud& Instance();

	void Update(float time);
	void Draw();

	void AddComponent(IHudComponent* comp);
};