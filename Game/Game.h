#pragma once
#include <string>
#include <vector>
#include "Engine.h"
#include <memory>
#include "Config.h"
class State;

class Game
{
public:
	Game();
	~Game();
	void Init() const;
	void ChangeState(std::unique_ptr<State>&& state);
	void PopState();
	void Quit() const;
	void HandleEvents();
	void Update(int time);
	void Draw();
private:
	// the stack of states
	std::vector<std::unique_ptr<State>> _states;

	Engine _mainManager;
};

