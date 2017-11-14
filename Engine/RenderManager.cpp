//
// Created by Ahmad Rahimi on 9/25/17.
//

#include "RenderManager.h"


RenderManager* RenderManager::renderManager;

RenderManager::RenderManager(): window(nullptr), renderer(nullptr)
{
}

RenderManager::~RenderManager() {
	SDL_DestroyWindow(this->window);
}

void RenderManager::CreateWindow(const std::string& title, bool fullscreen, const int width, const int height)
{
	auto flags = 0;
	if(fullscreen)
	{
		flags = SDL_WINDOW_FULLSCREEN;
	}

	const auto resp = SDL_CreateWindowAndRenderer(width, height, flags, &this->window, &this->renderer);
	if (resp != 0) {
		std::cout << SDL_GetError() << std::endl;
	}
	SDL_SetWindowTitle(this->window, title.c_str());
}

SDL_Surface* RenderManager::LoadImage(const std::string &filePath) {
	if (this->sprites.count(filePath) == 0) {
		this->sprites[filePath] = IMG_Load(filePath.c_str());
	}
	return this->sprites[filePath];
}

void RenderManager::BlitSurface(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle,
	double angle) const
{
	const auto resp = SDL_RenderCopyEx(this->renderer, texture, sourceRectangle, destinationRectangle, angle, NULL, SDL_FLIP_HORIZONTAL);
	if (resp != 0) {
		std::cout << SDL_GetError() << std::endl;
	}
}

RenderManager* RenderManager::GetRenderManager() {
	if (!renderManager) {
		renderManager = new RenderManager;
	}
	return renderManager;
}

void RenderManager::Flip() const
{
	SDL_RenderPresent(this->renderer);
}

void RenderManager::Clear() const
{
	SDL_RenderClear(this->renderer);
}

SDL_Renderer* RenderManager::GetRenderer() const {
	return this->renderer;
}