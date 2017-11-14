// This is the main DLL file.
#include "Engine.h"
#include <SDL.h>
#include <iostream>

Engine::Engine()
{
}

Engine::~Engine()
{
	SDL_Quit();
}

void Engine::Init() const
{
	/* Initialize defaults, Video and Audio */
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) == -1) {
		std::cout << SDL_GetError() << std::endl;
		exit(-1);
	}
}
