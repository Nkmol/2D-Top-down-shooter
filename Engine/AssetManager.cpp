#pragma once

#include "AssetManager.h"
#include <memory>

//AssetManager* AssetManager::instance()
//{
//	// TODO to refernece, can never be nullptr (should never)
//	static AssetManager* sInstance;
//
//	return sInstance;
//}

AssetManager::AssetManager() {
    sounds["pokemon"] = "../content/audio/Pokemon.wav";
	sounds["mainmenu"] = "../content/audio/mainmenu.mp3";
    effect["headshot"] = "../content/audio/Headshot.wav";
    render["roguelikeCity_magenta.png"] = "../content/map/roguelikeCity_magenta.png";
    render["half life.png"] = "../content/map/half life.png";
    render["soldier"] = "../content/soldier.png";
    render["soldier-idle-0"] = "../content/reload/survivor-reload_rifle_0.png";
    render["soldier-idle-1"] = "../content/reload/survivor-reload_rifle_1.png";
    render["soldier-idle-2"] = "../content/reload/survivor-reload_rifle_2.png";
    render["soldier-idle-3"] = "../content/reload/survivor-reload_rifle_3.png";
    render["soldier-idle-4"] = "../content/reload/survivor-reload_rifle_4.png";
    render["soldier-idle-5"] = "../content/reload/survivor-reload_rifle_5.png";
    render["soldier-idle-6"] = "../content/reload/survivor-reload_rifle_6.png";
    render["soldier-idle-7"] = "../content/reload/survivor-reload_rifle_7.png";
    render["soldier-idle-8"] = "../content/reload/survivor-reload_rifle_8.png";
    render["soldier-idle-9"] = "../content/reload/survivor-reload_rifle_9.png";
    render["soldier-idle-10"] = "../content/reload/survivor-reload_rifle_10.png";
    render["soldier-idle-11"] = "../content/reload/survivor-reload_rifle_11.png";
    render["soldier-idle-12"] = "../content/reload/survivor-reload_rifle_12.png";
    render["soldier-idle-13"] = "../content/reload/survivor-reload_rifle_13.png";
    render["soldier-idle-14"] = "../content/reload/survivor-reload_rifle_14.png";
    render["soldier-idle-15"] = "../content/reload/survivor-reload_rifle_15.png";
    render["soldier-idle-16"] = "../content/reload/survivor-reload_rifle_16.png";
    render["soldier-idle-17"] = "../content/reload/survivor-reload_rifle_17.png";
    render["soldier-idle-18"] = "../content/reload/survivor-reload_rifle_18.png";
    render["soldier-idle-19"] = "../content/reload/survivor-reload_rifle_19.png";
    render["boid"] = "../content/boid.png";
    render["bullet"] = "../content/bullet.png";
	fonts["Sans Regular"] = "../content/fonts/OpenSans-Regular.ttf";
	render["newgamebutton"] = "../content/menu/button_new-game.png";
	render["loadgamebutton"] = "../content/menu/button_load-game.png";
	render["creditsbutton"] = "../content/menu/button_credits.png";
	render["mutebutton"] = "../content/menu/audio-unmute2.png";
	render["quitbutton"] = "../content/menu/button_quit.png";
    //render["background"] = "../Assets/Img/wallpaper.png";

    //enemies
    render["zombieenemy"] = "../content/zombie_1.png";
    render["batenemy"] = "../content/bat.png";
	render["space.jpg"] = "../content/map/space.jpg";

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

Mix_Music *AssetManager::loadBGM(string soundToken) {
    //Load music
    Mix_Music *gBGM = Mix_LoadMUS(sounds[soundToken]);
    if (gBGM == NULL) {
        cout << "failed to load" << Mix_GetError() << endl;
        return nullptr;
    }
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
	TTF_Font* font  = TTF_OpenFont(fonts[fontToken], size);
	if (font == NULL)
		cout << "Unable to load font %s! SDL_image Error: " << render[fontToken] << TTF_GetError() << endl;

	return font;
}

SDL_Texture * AssetManager::loadTexture(string mediaToken)
{
	SDL_Surface *surface = loadSurface(mediaToken);
	if (!surface)
		cout << SDL_GetError() << endl;
	SDL_Texture* texture = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);


	if (texture == NULL) {
		printf(SDL_GetError());
	}
	return texture;
}
