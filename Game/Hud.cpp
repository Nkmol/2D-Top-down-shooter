#include "Hud.h"

Hud& Hud::Instance()
{
	static Hud _instance;

	return _instance;
}

Hud::Hud()
{

}

void Hud::Update(float time)
{
	for (auto comps : _components)
		comps->Update(time);
}

void Hud::Draw()
{
	for (auto comps : _components)
		comps->Draw();
}

void Hud::AddComponent(IHudComponent* comp)
{
	_components.push_back(std::move(comp));
}

