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

void RenderManager::apply_surface(int x, int y, SDL_Surface * source, SDL_Surface * destination)
 {
		//Make a temporary rectangle to hold the offsets
	SDL_Rect offset;
	
			//Give the offsets to the rectangle
	offset.x = x;
	offset.y = y;
	
			//Blit the surface
		SDL_BlitSurface(source, NULL, destination, &offset);
}

void RenderManager::AddMenuSurfaces(int screen_width, int screen_height) 
{
	SDL_Surface* windowSurface = SDL_GetWindowSurface(this->window);
	SDL_Surface* newgame = AssetManager::getInstance().loadSurface("newgamebutton");
	SDL_Surface* loadgame = AssetManager::getInstance().loadSurface("loadgamebutton");
	SDL_Surface* credits = AssetManager::getInstance().loadSurface("creditbutton");

	this->apply_surface(screen_width / 3, (screen_height / 3) * 0.75, newgame, windowSurface);
	this->apply_surface(screen_width / 3, (screen_height / 3) * 1.25, loadgame, windowSurface);
	this->apply_surface(screen_width / 3, (screen_height / 3) * 1.75, credits, windowSurface);

}

RenderManager& RenderManager::Instance() {
	static RenderManager sInstance; // Guaranteed to be destroyed.
								    // Instantiated on first use.

	return sInstance;
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

SDL_Window* RenderManager::GetWindow() const {
	return this->window;
}