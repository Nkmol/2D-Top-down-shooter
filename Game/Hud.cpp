#include "Hud.h"
#include <algorithm>

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

	auto y(std::remove_if(_components.begin(), _components.end(), [](IHudComponent* c) { return c->Destroyable(); }));
	_components.erase(y, _components.end());
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

