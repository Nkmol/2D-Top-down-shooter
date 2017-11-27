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
    render["roguelikeCity_magenta.png"] = "../content/map/roguelikeCity_magenta.png";
    render["half life.png"] = "../content/map/half life.png";
    render["soldier"] = "../content/soldier.png";
    render["boid"] = "../content/boid.png";
    render["bullet"] = "../content/bullet.png";
	fonts["Sans Regular"] = "../content/fonts/OpenSans-Regular.ttf";
	render["newgamebutton"] = "../content/menu/button_new-game.bmp";
	render["loadgamebutton"] = "../content/menu/button_load-game.bmp";
	render["creditsbutton"] = "../content/menu/button_credits.bmp";
    //render["background"] = "../Assets/Img/wallpaper.png";
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);
	TTF_Init();
}


AssetManager &AssetManager::getInstance() {
    // The only instance
    // Guaranteed to be lazy initialized
    // Guaranteed that it will be destroyed correctly

    static AssetManager sInstance;
    return sInstance;
}

Mix_Music *AssetManager::loadBGM(string soundToken) {
    //Load music
    Mix_Music *gBGM = Mix_LoadMUS(sounds[soundToken]);
    if (gBGM == NULL) {
        cout << "failed to load" << Mix_GetError() << endl;
        return nullptr;
    }
    cout << "works" << Mix_GetError() << endl;
    return gBGM;
}

Mix_Chunk *AssetManager::loadEffect(string effectToken) {
    Mix_Chunk *gEffectM = Mix_LoadWAV(effect[effectToken]);
    if (gEffectM == NULL) {
        cout << "Failed to load scratch sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
        return nullptr;
    }
    return gEffectM;
}

SDL_Surface *AssetManager::loadSurface(string mediaToken) {
    //Load image at specified path
    SDL_Surface *loadedSurface = IMG_Load(render[mediaToken]);
    if (loadedSurface == NULL) {
        cout << "Unable to load image %s! SDL_image Error: " << render[mediaToken] << IMG_GetError() << endl;
    }

    return loadedSurface;
}

TTF_Font* AssetManager::loadFont(string fontToken, const int size)
{
	TTF_Font* font = TTF_OpenFont(fonts[fontToken], size);
	if (font == NULL)
		cout << "Unable to load font %s! SDL_image Error: " << render[fontToken] << TTF_GetError() << endl;

	return font;
}