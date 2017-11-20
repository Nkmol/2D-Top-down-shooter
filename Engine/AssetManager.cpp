#pragma once

#include "AssetManager.h"

//AssetManager* AssetManager::instance()
//{
//	// TODO to refernece, can never be nullptr (should never)
//	static AssetManager* sInstance;
//
//	return sInstance;
//}

AssetManager::AssetManager() {
	sounds["pokemon"] = "../content/audio/Pokemon.wav";
	effect["headshot"] = "../content/audio/Headshot.wav";
	render["creditbutton"] = "../content/img/button_credits.bmp";
	render["loadgamebutton"] = "../content/img/button_load-game.bmp";
	render["newgamebutton"] = "../content/img/button_new-game.bmp";
	//render["background"] = "../Assets/Img/wallpaper.png";
}


AssetManager & AssetManager::getInstance()
{
	// The only instance
	// Guaranteed to be lazy initialized
	// Guaranteed that it will be destroyed correctly

	static AssetManager sInstance;
	return sInstance;
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