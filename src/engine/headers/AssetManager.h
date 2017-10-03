#pragma once

#include "SDL.h"
#include "SDL_audio.h"
#include "SDL_mixer.h"
#include <map>
#include <iostream>
#include <SDL_image.h>

class AssetManager {

private:
	std::map<std::string, const char* > sounds;
	std::map<std::string, const char* > effect;
	std::map<std::string, const char* > render;
	static AssetManager* sInstance;
public:
	AssetManager();
	static AssetManager* instance();
	Mix_Music* loadBGM(std::string soundToken);
	Mix_Chunk* loadEffect(std::string effectToken);
	SDL_Surface* loadSurface(std::string mediaToken);
}; 