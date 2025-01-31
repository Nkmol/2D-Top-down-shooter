//
// Created by Ahmad Rahimi on 9/25/17.
//

#include "RenderManager.h"
#include "CustomDeleter.h"
#include "AssetManager.h"

RenderManager::RenderManager(): _window(nullptr), _renderer(nullptr)
{
}

RenderManager::~RenderManager() {
	SDL_DestroyWindow(this->_window);
}

void RenderManager::CreateWindow(const std::string& title, bool fullscreen, const int width, const int height)
{
	//auto flags = SDL_RENDERER_ACCELERATED;
	if(fullscreen)
	{
		//flags = SDL_WINDOW_FULLSCREEN | SDL_RENDERER_ACCELERATED;
	}

	const auto resp = SDL_CreateWindowAndRenderer(width, height, 0,&this->_window, &this->_renderer);
	if (resp != 0) {
		std::cout << SDL_GetError() << std::endl;
	}
	SDL_SetWindowTitle(this->_window, title.c_str());
}

SDL_Surface* RenderManager::LoadImage(const std::string &filePath) {
	if (this->_sprites.count(filePath) == 0) {
		this->_sprites[filePath] = IMG_Load(filePath.c_str());
	}
	return this->_sprites[filePath];
}

void RenderManager::DrawTexture(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle,
	double angle) const
{
	const auto resp = SDL_RenderCopyEx(this->_renderer, texture, sourceRectangle, destinationRectangle, angle, NULL, SDL_FLIP_NONE);
	if (resp != 0) {
		std::cout << SDL_GetError() << std::endl;
	}
}

RenderManager& RenderManager::Instance() {
	static RenderManager _instance; // Guaranteed to be destroyed.
								    // Instantiated on first use.

	return _instance;
}

void RenderManager::Render() const
{
	SDL_RenderPresent(this->_renderer);
}

void RenderManager::Clear() const
{
	SDL_RenderClear(this->_renderer);
}

SDL_Renderer* RenderManager::GetRenderer() const {
	return this->_renderer;
}

SDL_Window* RenderManager::GetWindow() const {
	return this->_window;
}