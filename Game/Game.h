#pragma once
#include <string>
#include <vector>
#include "Engine.h"
#include <memory>

class State;

class Game
{
public:
	Game();
	~Game();
	void Init(const std::string& title, bool fullscreen, const int width, const int height) const;
	void ChangeState(std::unique_ptr<State>&& state);
	void Quit() const;
	void Run(unsigned fps);
	void HandleEvents();
	void Update(float time);
	void Draw();
private:
	// the stack of states
	std::vector<std::unique_ptr<State>> _states;

	Engine _mainManager;
};

