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
	void Quit();
	void Run(const unsigned fps);
	void HandleEvents();
	void Update(float time);
	void Draw();
private:
	// the stack of states
	std::vector<std::unique_ptr<State>> _states;
	bool isRunning;
	Engine _mainManager;
};

