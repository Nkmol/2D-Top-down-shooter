#pragma once

#include "SDL.h"
#include "SDL_audio.h"
#include "SDL_mixer.h"
#include <map>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include "../CustomDeleter.h"


using namespace std;

class AssetManager {

private:
	AssetManager();

public:

	static AssetManager& Instance();
	AssetManager(AssetManager const&) = delete;
	void operator=(AssetManager const&) = delete;
	//static AssetManager* instance();
	Mix_Music* loadBGM(string soundToken);
	Mix_Chunk* loadEffect(string effectToken);
	SDL_Surface* loadSurface(string mediaToken);

	TTF_Font* loadFont(string fontToken, const int size);
};