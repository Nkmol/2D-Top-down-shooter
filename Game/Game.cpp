#include "Game.h"
#include "RenderManager.h"
#include "Engine.h"
#include "State.h"
#include "MapManager.h"
#include "TickerTime.h"
#include <algorithm>

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

void Game::Quit()
{
	isRunning = false;
}

void Game::Run(const unsigned int fps)
{
	TickerTime ticker{fps, 100};

	const auto frameTime = fps / 100.0f;
	isRunning = true;
	while (isRunning)
	{
		HandleEvents();

		auto deltaTime = ticker.GetDeltaTime();

		// To create constant update sequence
		do
		{
			Update(deltaTime);
			deltaTime -= frameTime;
		}
		while (deltaTime >= frameTime);

		Draw();
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

	_states.back()->Draw(*this);
	renderManager.Flip();
}
