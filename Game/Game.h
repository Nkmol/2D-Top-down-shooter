#pragma once
#include <string>
#include "Engine.h"

class Game
{
public:
	Game();
	~Game();
	void Init(const std::string& title, bool fullscreen, const int width, const int height) const;
private:
	Engine _mainManager;
};

