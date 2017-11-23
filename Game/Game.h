#pragma once
#include <string>
#include <vector>
#include "Engine.h"

class State;

class Game
{
public:
	Game();
	~Game();
	void Init(const std::string& title, bool fullscreen, const int width, const int height) const;
	void ChangeState(State* state);
	void PopState();
	void Quit() const;
	void HandleEvents();
	void Update(int time);
	void Draw();
private:
	// the stack of states
	std::vector<State*> _states;

	Engine _mainManager;
};

