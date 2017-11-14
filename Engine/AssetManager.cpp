#pragma once

#include "AssetManager.h"

//how to call: AssetManager::instance()->loadBGM();
AssetManager* AssetManager::instance()
{
	// TODO to refernece, can never be nullptr (should never)
	static AssetManager* sInstance;

	return sInstance;
}

AssetManager::AssetManager() {
	sounds["pokemon"] = "../content/Audio/Pokemon.wav";
	effect["headshot"] = "../content/Audio/Headshot.wav";
	render["background"] = "../Assets/Img/wallpaper.png";
	render["roguelikeCity_magenta.png"] = "../content/map/roguelikeCity_magenta.png";
}


Mix_Music* AssetManager::loadBGM(string soundToken)
{
	//Load music
	Mix_Music* gBGM = Mix_LoadMUS(sounds[soundToken]);
	if (gBGM == NULL)
	{
		cout << "failed to load" << Mix_GetError() << endl;
		return nullptr;
	}
	cout << "works" << Mix_GetError() << endl;
	return gBGM;
}

Mix_Chunk* AssetManager::loadEffect(string effectToken)
{
	Mix_Chunk* gEffectM = Mix_LoadWAV(effect[effectToken]);
	if (gEffectM == NULL)
	{
		cout << "Failed to load scratch sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
		return nullptr;
	}
	return gEffectM;
}

SDL_Surface* AssetManager::loadSurface(string mediaToken)
{
	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load(render[mediaToken]);
	if (loadedSurface == NULL)
	{
		cout << "Unable to load image %s! SDL_image Error: " << render[mediaToken] << IMG_GetError() << endl;
	}

	return loadedSurface;
}