#include "Hud.h"
#include <algorithm>


Hud& Hud::Instance()
{
	static Hud _instance;

	return _instance;
}

Hud::Hud() = default;

void Hud::Update(float time)
{
	for (auto it = _components.begin(); it != _components.end();) {
		auto& kv = *it;

		if(kv.second->Destroyable())
		{
			it = _components.erase(it);
		}
		else
		{
			kv.second->Update(time);
			 ++it;
		}
	}
}

void Hud::Draw()
{
	for (const auto& kv : _components) {
		kv.second->Draw();
	}
}

void Hud::AddComponent(const std::string & identifier, std::unique_ptr<Base>&& comp)
{
	_components.emplace(identifier, std::move(comp));
}
