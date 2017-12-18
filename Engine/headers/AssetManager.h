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
#include "RenderManager.h"


using namespace std;

class AssetManager {

private:
	AssetManager();

public:

	static AssetManager& Instance();
	AssetManager(AssetManager const&) = delete;
	void operator=(AssetManager const&) = delete;

	Mix_Music* LoadBGM(const string soundToken);
	Mix_Chunk* LoadEffect(const string effectToken);
	SDL_Surface* LoadSurface(const string mediaToken);
	static std::unique_ptr<SDL_Texture, CustomDeleter> LoadTexture(const std::string& str);
	TTF_Font* LoadFont(const string fontToken, const int size);
};