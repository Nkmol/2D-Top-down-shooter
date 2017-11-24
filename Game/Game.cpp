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

void Game::Init(const std::string& title, bool fullscreen, const int width, const int height) const
{
	_mainManager.Init();
	RenderManager::Instance().CreateWindow(title, fullscreen, width, height);

	MapManager::Instance().Init("../content/map/halflife.tmx");
}

// Explicity force user to transfer ownership with std::move
void Game::ChangeState(unique_ptr<State>&& state)
{
	// Move ownership to the state vector
	_states.push_back(std::move(state));
	_states.back()->Init();
}

void Game::Quit() const
{
	exit(0);
}

void Game::Run(const unsigned int fps)
{
	TickerTime ticker{ fps, 100 };

	const auto gameIsRunning = true;
	while (gameIsRunning) {
		HandleEvents();

		const auto deltaTime = ticker.GetDeltaTime();
		Update(deltaTime);

		Draw();

		// To create constant update sequence
		ticker.WaitNextUpdate();
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
