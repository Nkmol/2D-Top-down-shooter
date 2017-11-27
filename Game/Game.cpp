#include "Game.h"
#include "RenderManager.h"
#include "Engine.h"
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

void Game::Init() const
{
	_mainManager.Init();
	RenderManager::Instance().CreateWindow(config::title, config::fullscreen, config::width, config::height);

	MapManager::Instance().Init("../content/map/halflife.tmx");
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

void Game::Quit() const
{
	exit(0);
}

void t()
{
	// TODO: Split physics and non-physic logic with 2 different updates
	// update at a fixed rate each time
	//Update(1 / static_cast<float>(1)); // ticks to seconds
}

void Game::Run(const unsigned int targetFps)
{
	TickerTime timer{targetFps, 120};

	timer.OnCatchUp([&]()
	{
		// TODO: Split physics and non-physic logic with 2 different updates
		// update at a fixed rate each time
		Update(timer.GetGameTime()); // ticks to seconds
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

	const auto gameIsRunning = true;
	timer.Run(gameIsRunning);
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
