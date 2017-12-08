#pragma once

#include "AssetManager.h"

AssetManager::AssetManager() {

	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();
}

AssetManager &AssetManager::Instance() {
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly

	static AssetManager sInstance;
	return sInstance;
}

Mix_Music *AssetManager::LoadBGM(const string soundToken) {
	//Load music
	Mix_Music *gBGM = Mix_LoadMUS(string{ "../content/audio/" + soundToken + ".wav" }.c_str());
	if (gBGM == NULL) {
		gBGM = Mix_LoadMUS(string{ "../content/audio/" + soundToken + ".mp3" }.c_str());
	}
	if (gBGM == NULL) {
		cout << "failed to load" << Mix_GetError() << endl;
	}
	return gBGM;
}

Mix_Chunk *AssetManager::LoadEffect(const string effectToken) {
	Mix_Chunk *gEffectM = Mix_LoadWAV(string{ "../content/audio/" + effectToken + ".wav" }.c_str());
	if (gEffectM == NULL) {
		cout << "Failed to load scratch sound effect! SDL_mixer Error: " << effectToken.c_str() << Mix_GetError() << endl;
	}
	return gEffectM;
}

SDL_Surface *AssetManager::LoadSurface(const string mediaToken) {
	//Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(string{ "../content/sprites/" + mediaToken + ".png" }.c_str());

	if (loadedSurface == NULL) {
		loadedSurface = IMG_Load(string{ "../content/sprites/" + mediaToken + ".jpg" }.c_str());
	}
	if (loadedSurface == NULL) {
		loadedSurface = IMG_Load(string{ "../content/map/" + mediaToken }.c_str());
	}

	if (loadedSurface == NULL) {
		cout << "Unable to load image! SDL_image Error: " << mediaToken.c_str() << IMG_GetError() << endl;
	}

	return loadedSurface;
}


TTF_Font* AssetManager::LoadFont(const string fontToken, const int size)
{
	TTF_Font *font = TTF_OpenFont(string{ "../content/fonts/" + fontToken + ".ttf" }.c_str(), size);
	if (font == NULL)
		cout << "Unable to load font! SDL_image Error: " << fontToken.c_str() << TTF_GetError() << endl;

	return font;
}

SDL_Texture * AssetManager::LoadTexture(string mediaToken)
{
	SDL_Surface *surface = LoadSurface(mediaToken);
	if (!surface)
		cout << SDL_GetError() << endl;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);


	if (texture == NULL) {
		cout << "Unable to load texture! SDL_image Error: " << mediaToken.c_str() << TTF_GetError() << endl;
	}
	return texture;
}