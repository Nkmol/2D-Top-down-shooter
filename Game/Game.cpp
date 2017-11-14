#include "Game.h"
#include "RenderManager.h"
#include "Engine.h"

Game::Game()
{
	_mainManager = Engine();
}

Game::~Game()
{
}

void Game::Init(const std::string& title, bool fullscreen, const int width, const int height) const
{
	_mainManager.Init();

	RenderManager::Instance().CreateWindow(title, fullscreen, width, height);
}
