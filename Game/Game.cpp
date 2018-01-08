#include "Game.h"
#include "State.h"
#include "TickerTime.h"
#include <algorithm>
#include <thread>
#include <iomanip>
#include "RenderManager.h"
#include "Config.h"
#include "Level.h"

Game::Game() = default;

Game::~Game() = default;

void Game::Init()
{
	_mainManager.Init();
	RenderManager::Instance().CreateWindow(config::title, config::fullscreen, config::width, config::height);

	// Init after window renderer has been created
	_fpsUI = std::move(UIText{ "0.00", 16,{ 2, 2 } });
}

// Explicity force user to transfer ownership with std::move
void Game::ChangeState(unique_ptr<State>&& state)
{
	// Move ownership to the state vector
	_states.push_back(std::move(state));
	_states.back()->Init(*this);
}

void Game::SetState(unique_ptr<State>&& state)
{
	ClearStates();
	ChangeState(move(state));
}

const unique_ptr<State>& Game::GetStateBack(const int at)
{
	return _states.end()[- (at+1)];
}

void Game::PopState(unsigned val)
{
	while (val > 0 && val <= _states.size()) {
		PopState();
		val = val - 1;
	}
}

void Game::PopState()
{
	_states.pop_back();
}

void Game::ClearStates()
{
	_states.clear();
}

void Game::Quit()
{
	_isRunning = false;
}

void Game::Run(const unsigned int targetFps)
{
	// Reference explenation: http://gamesfromwithin.com/casey-and-the-clearly-deterministic-contraptions
	// Reference code example: https://gist.github.com/mariobadr/673bbd5545242fcf9482

	TickerTime timer{targetFps, 120};

	#pragma region init timer
	timer.OnCatchUp([&]()
	{
		// TODO: Split physics and non-physic logic with 2 different updates
		// update at a fixed rate each time
		Update(timer.GetGameTime());
	});

	timer.OnFrame([&]()
	{
		// TODO: Support interpolation between 2 drawing states -> will smooth the rendering
		Draw();
		HandleEvents();
	});

	timer.PerSecond(1, [&]()
	{
		_fps = timer.GetFps();
	});
	#pragma endregion 

	_isRunning = true;;
	timer.Run(_isRunning);
}

void Game::HandleEvents()
{
	auto &inputManager = InputManager::Instance();

	Event event;
	while (inputManager.HasEvent(&event)) {
		if (inputManager.IsQuit(event)) {
			Quit();
			return;
		}

		_states.back()->HandleEvents(*this, event);
	}
}

void Game::Update(float time)
{
	_states.back()->Update(*this, time);
}

void Game::Draw()
{
	auto& renderManager = RenderManager::Instance();
	renderManager.Clear();
	_states.back()->Draw(*this);

	// Fps to string and 2 decimal
	std::stringstream str;
	str << fixed << std::setprecision(0) << _fps;
	_fpsUI.ChangeText(str.str());
	_fpsUI.Draw();

	renderManager.Render();
}
