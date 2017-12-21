#pragma once

#include "SDL.h"
#include "SDL_audio.h"
#include "SDL_mixer.h"
#include <map>
#include <iostream>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <memory>
#include "RenderManager.h"
#include "../CustomDeleter.h"
#include <memory>

using namespace std;

class Texture;

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
	static std::unique_ptr<Texture> LoadTexture(const std::string& str);

	typedef unique_ptr<TTF_Font, CustomDeleter> Font;
	Font LoadFont(const string & fontToken, const int size) const;
};