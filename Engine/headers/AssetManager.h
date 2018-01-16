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
#include <json.hpp>
#include "../Font.h"

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
	nlohmann::json LoadJson(const std::string& path) const;

	typedef std::unique_ptr<SDL_Surface, CustomDeleter> Surface;
	SDL_Surface* LoadSurface(const string mediaToken);

	static std::unique_ptr<Texture> LoadTexture(const std::string& str);

	void SaveJson(const nlohmann::json & json, const std::string savedGame) const;

	Font LoadFont(const string & fontToken, const int size) const;
};