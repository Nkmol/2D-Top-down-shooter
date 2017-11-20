#include "Game.h"
#include "RenderManager.h"
#include "Engine.h"
#include "State.h"
#include "TMXManager.h"

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

	TMXManager::Instance().Init("../content/map/tilemapje2.tmx");
}

void Game::ChangeState(State* state)
{
	// cleanup the current state
	/*if (!_states.empty()) {
		_states.back()->Cleanup();
		_states.pop_back();
	}*/

	// store and init the new state
	_states.push_back(state);
	_states.back()->Init();
}

void Game::Quit() const
{
	exit(0);
}

void Game::HandleEvents()
{
	_states.back()->HandleEvents(*this);
}

void Game::Update(int time)
{
	_states.back()->Update(*this, time);
}

void Game::Draw()
{
	auto& renderManager = RenderManager::Instance();
	renderManager.Clear();
	TMXManager::Instance().Render();

	_states.back()->Draw(*this);
	renderManager.Flip();
}
