#pragma once
#include <map>
#include "AIBat.h"

class IAIBase;

class FactoryBehaviour
{
	typedef std::unique_ptr<IAIBase>(*CreatorFunc)();

	std::map<std::string, CreatorFunc> _processors;

	template <typename T>
	static unique_ptr<IAIBase> Creator() {
		return make_unique<T>();
	}

	FactoryBehaviour()
	{
		_processors["default"] = Creator<AIDefault>;
		_processors["bat"] = Creator<AIBat>;
	}
public:
	FactoryBehaviour(FactoryBehaviour const&) = delete;
	void operator=(FactoryBehaviour const&) = delete;

	unique_ptr<IAIBase> Create(const std::string& str)
	{
		auto& result = _processors[str];

		/*if (!result)
			return nullptr;*/
		
		return _processors[str]();
	}

	static FactoryBehaviour& Instance() {
		// The only instance
		// Guaranteed to be lazy initialized
		// Guaranteed that it will be destroyed correctly

		static FactoryBehaviour _instance;
		return _instance;
	}
};

