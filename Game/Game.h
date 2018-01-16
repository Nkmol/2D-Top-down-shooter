#pragma once
#include <vector>
#include "Engine.h"
#include <memory>
#include "../Engine/UIText.h"

class Level;
class State;

class Game
{
	// the stack of states
	std::vector<std::unique_ptr<State>> _states;
	bool _isRunning;
	Engine _mainManager;
	double _fps;
	std::shared_ptr<Level> _level;
public:
	Game();
	~Game();
	void Init();
	void ChangeState(std::unique_ptr<State>&& state);
	void SetState(std::unique_ptr<State>&& state);
	// Get state starting at back (1 is before last)
	const std::unique_ptr<State>& GetStateBack(const int at);
	void PopState(unsigned val);
	void PopState();
	void ClearStates();
	void Quit();
	void Run(const unsigned int fps);
	void HandleEvents();
	void Update(float time);
	void Draw();	
};

