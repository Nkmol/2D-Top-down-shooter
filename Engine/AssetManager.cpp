#pragma once

#include "AssetManager.h"
#include "Texture.h"

AssetManager::AssetManager() {

    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
    TTF_Init();
}

AssetManager &AssetManager::Instance() {
    // The only instance
    // Guaranteed to be lazy initialized
    // Guaranteed that it will be destroyed correctly

    static AssetManager _instance;
    return _instance;
}

Mix_Music *AssetManager::LoadBGM(const string soundToken) {
    //Load music
    Mix_Music *_bgm = Mix_LoadMUS(string{"../content/audio/" + soundToken + ".wav"}.c_str());
    if (_bgm == NULL) {
        _bgm = Mix_LoadMUS(string{"../content/audio/" + soundToken + ".mp3"}.c_str());
    }
    if (_bgm == NULL) {
        cout << "failed to load" << Mix_GetError() << endl;
    }
    return _bgm;
}

Mix_Chunk *AssetManager::LoadEffect(const string effectToken) {
    Mix_Chunk *_effectMusic = Mix_LoadWAV(string{"../content/audio/" + effectToken + ".wav"}.c_str());
    if (_effectMusic == NULL) {
        cout << "Failed to load scratch sound effect! SDL_mixer Error: " << effectToken.c_str() << Mix_GetError()
             << endl;
    }
    return _effectMusic;
}

SDL_Surface *AssetManager::LoadSurface(const string mediaToken) {
    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(string{"../content/sprites/" + mediaToken + ".png"}.c_str());

    if (loadedSurface == NULL) {
        loadedSurface = IMG_Load(string{"../content/sprites/" + mediaToken + ".jpg"}.c_str());
    }
    if (loadedSurface == NULL) {
        loadedSurface = IMG_Load(string{"../content/map/" + mediaToken}.c_str());
    }

    if (loadedSurface == NULL) {
//		cout << "Unable to load image! SDL_image Error: " << mediaToken.c_str() << IMG_GetError() << endl;
    }

    return loadedSurface;
}


TTF_Font *AssetManager::LoadFont(const string fontToken, const int size) {
    TTF_Font *_font = TTF_OpenFont(string{"../content/fonts/" + fontToken + ".ttf"}.c_str(), size);
    if (_font == NULL)
        cout << "Unable to load font! SDL_image Error: " << fontToken.c_str() << TTF_GetError() << endl;

    return _font;
}

std::unique_ptr<Texture> AssetManager::LoadTexture(const std::string& str)
{
	if (str.empty()) return {};

	// TODO call this from RenderManager, so it gives the Render instance as parameter to this function (DI)
	const auto texture = IMG_LoadTexture(RenderManager::Instance().GetRenderer(), ("../content/sprites/" + str + ".png").c_str());
	if (texture == nullptr)
	{
		std::cout << "Failed to load texture " << str << ". Error: " << SDL_GetError() << std::endl;
	}
	return make_unique<Texture>(texture);
}
