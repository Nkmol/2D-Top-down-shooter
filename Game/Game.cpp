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

void Game::Run(const unsigned int targetFps)
{
	const auto ticksPerSecond = SDL_GetPerformanceFrequency();
	const auto targetTicksPerFrame = ticksPerSecond / targetFps;
	auto currentTime = SDL_GetPerformanceCounter();
	auto accumulator = 0.0;
	auto t = 0;
	while (!false)
	{
		const auto time = SDL_GetPerformanceCounter();
		const auto deltaTime = time - currentTime;
		currentTime = time;

		accumulator += deltaTime;

		// update game logic as lag permits -> physics catch up
		while (accumulator >= targetTicksPerFrame)
		{
			// update at a fixed rate each time
			Update(targetTicksPerFrame / static_cast<float>(ticksPerSecond)); // ticks to seconds

			accumulator -= targetTicksPerFrame;
		}

		// Draw only once per sec
		if (t % targetFps == 0)
		{
			_fps = static_cast<float>(ticksPerSecond) / deltaTime;
		}

		Draw();
		t++;
		HandleEvents();
	}
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
