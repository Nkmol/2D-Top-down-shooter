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

	auto y(std::remove_if(_components.begin(), _components.end(), [](UIElement* c) { return c->Destroyable(); }));
	_components.erase(y, _components.end());
}

void Hud::Draw()
{
	for (auto comps : _components)
		comps->Draw();
}

void Hud::AddComponent(UIElement* comp)
{
	_components.push_back(comp);
}

void Hud::RemoveComponent(UIElement* comp)
{
	auto y(std::remove_if(_components.begin(), _components.end(), [&comp](UIElement* c) { return c == comp; }));
	_components.erase(y, _components.end());
}
