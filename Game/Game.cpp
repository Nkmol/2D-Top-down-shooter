#include "Game.h"
#include "RenderManager.h"
#include "State.h"
#include "MapManager.h"
#include "TickerTime.h"
#include <algorithm>
#include <thread>
#include <iomanip> 

Game::Game()
{
}

Game::~Game()
{
}

void Game::Init()
{
	_mainManager.Init();
	RenderManager::Instance().CreateWindow(config::title, config::fullscreen, config::width, config::height);

	_level = make_shared<Level>(1);
}

// Explicity force user to transfer ownership with std::move
void Game::ChangeState(unique_ptr<State>&& state)
{
	// Move ownership to the state vector
	_states.push_back(std::move(state));
	_states.back()->Init();
}

void Game::PopState()
{
	_states.pop_back();
}

void Game::Quit()
{
	isRunning = false;
}

void Game::Run(const unsigned int targetFps)
{
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

	isRunning = true;;
	timer.Run(isRunning);
}

void Game::HandleEvents()
{
	_states.back()->HandleEvents(*this);
}

void Game::Update(float time)
{
	_states.back()->Update(*this, time);
}

void Game::Draw()
{
	auto& renderManager = RenderManager::Instance();
	renderManager.Clear();
	MapManager::Instance().Render();

	// Fps to string and 2 decimal
	std::stringstream str;
	str << fixed << std::setprecision(2) << _fps;

	renderManager.DrawText(str.str(), 20, 20, 70, 20);

	_states.back()->Draw(*this);
	renderManager.Flip();
}

shared_ptr<Level> Game::GetLevel() const
{
	return _level;
}
