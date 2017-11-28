//
// Created by Ahmad Rahimi on 9/25/17.
//

#include "RenderManager.h"

RenderManager::RenderManager(): window(nullptr), renderer(nullptr)
{
}

RenderManager::~RenderManager() {
	SDL_DestroyWindow(this->window);
}

void RenderManager::CreateWindow(const std::string& title, bool fullscreen, const int width, const int height)
{
	//auto flags = SDL_RENDERER_ACCELERATED;
	if(fullscreen)
	{
		//flags = SDL_WINDOW_FULLSCREEN | SDL_RENDERER_ACCELERATED;
	}

	const auto resp = SDL_CreateWindowAndRenderer(width, height, 0,&this->window, &this->renderer);
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

void RenderManager::DrawTexture(SDL_Texture *texture, SDL_Rect *sourceRectangle, SDL_Rect *destinationRectangle,
	double angle) const
{
	const auto resp = SDL_RenderCopyEx(this->renderer, texture, sourceRectangle, destinationRectangle, angle, NULL, SDL_FLIP_HORIZONTAL);
	if (resp != 0) {
		std::cout << SDL_GetError() << std::endl;
	}
}

void RenderManager::DrawText(const std::string text, const int x, const int y, const int width, const int height, const double angle) const
{
	TTF_Font* font = AssetManager::Instance().loadFont("Sans Regular", height);
	SDL_Color color = { 255, 255, 255 };
	SDL_Surface* sMessage = TTF_RenderText_Solid(font, text.c_str(), color);
	SDL_Texture* message = SDL_CreateTextureFromSurface(renderer, sMessage);
	SDL_FreeSurface(sMessage);

	SDL_Rect messageRect;
	messageRect.x = x;
	messageRect.y = y;
	messageRect.w = width;
	messageRect.h = height;

	const auto resp = SDL_RenderCopyEx(renderer, message, NULL, &messageRect, angle, NULL, SDL_FLIP_NONE);
	if (resp != 0) {
		std::cout << SDL_GetError() << std::endl;
	}
}

RenderManager& RenderManager::Instance() {
	static RenderManager sInstance; // Guaranteed to be destroyed.
								    // Instantiated on first use.

	return sInstance;
}

void RenderManager::Render() const
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

SDL_Window* RenderManager::GetWindow() const {
	return this->window;
}