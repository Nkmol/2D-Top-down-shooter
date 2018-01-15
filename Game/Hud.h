#pragma once
#include "../Engine/UIElement.h"

class Hud
{
	static Hud* _instance;

	typedef UIElement Base;
	std::unordered_map<std::string, std::unique_ptr<UIElement>> _components;

	Hud();
public:
	Hud(Hud const&) = delete;
	void operator=(Hud const&) = delete;

	static Hud& Instance();

	void Update(float time);
	void Draw();

	template<typename T>
	T* Get(const std::string& id)
	{
		// Force cast to derrived
		return static_cast<T*>(_components.at(id).get());
	}

	// use r-value to force moving of ownership
	void AddComponent(const std::string& identifier, std::unique_ptr<Base>&& comp);
};
