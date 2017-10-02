#pragma once

#include "SDL.h"
#include "SDL_audio.h"
#include "SDL_mixer.h"
#include <map>
#include <iostream>
#include <SDL_image.h>


using namespace std;

class AssetManager {

private:
	map<string, const char* > sounds;
	map<string, const char* > effect;
	map<string, const char* > render;
	static AssetManager* sInstance;
public:
	AssetManager();
	static AssetManager* instance();
	Mix_Music* loadBGM(string soundToken);
	Mix_Chunk* loadEffect(string effectToken);
	SDL_Surface* loadSurface(string mediaToken);

}; 