#pragma once
#include <string>
#include <vector>
#include "Engine.h"
#include <memory>
#include "Config.h"
#include "Level.h"

class State;

class Game
{
	shared_ptr<Level> _level;
public:
	Game();
	~Game();
	void Init();
	void ChangeState(std::unique_ptr<State>&& state);
	void PopState();
	void Quit();
	void Run(const unsigned fps);
	void HandleEvents();
	void Update(float time);
	void Draw();
	shared_ptr<Level> GetLevel() const;
private:
	// the stack of states
	std::vector<std::unique_ptr<State>> _states;
	bool isRunning;
	Engine _mainManager;
};

