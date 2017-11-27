#include "Game.h"
#include "RenderManager.h"
#include "Engine.h"
#include "State.h"
#include "MapManager.h"
#include "TickerTime.h"
#include <algorithm>
#include <chrono>
#include <thread>
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
	TickerTime timer{ targetFps, 120 };

	timer.OnCatchUp([&]() {
		// TODO: Split physics and non-physic logic with 2 different updates
		// update at a fixed rate each time
		Update(timer.GetDeltaTime()); // ticks to seconds
	});

	timer.OnFrame([&]()
	{
		// TODO: Support interpolation between 2 drawing states -> will smooth the rendering
		Draw();
		//t++;
		HandleEvents();
	});

	auto gameIsRunning = true;
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
	renderManager.DrawText(std::to_string(_fps), 20, 20, 100, 20);

	_states.back()->Draw(*this);
	renderManager.Flip();
}
