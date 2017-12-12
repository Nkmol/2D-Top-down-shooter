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
    render["soldier-rifle-idle-0"] = "../content/player/rifle/idle/survivor-idle_rifle_0.png";
    render["soldier-rifle-idle-1"] = "../content/player/rifle/idle/survivor-idle_rifle_1.png";
    render["soldier-rifle-idle-2"] = "../content/player/rifle/idle/survivor-idle_rifle_2.png";
    render["soldier-rifle-idle-3"] = "../content/player/rifle/idle/survivor-idle_rifle_3.png";
    render["soldier-rifle-idle-4"] = "../content/player/rifle/idle/survivor-idle_rifle_4.png";
    render["soldier-rifle-idle-5"] = "../content/player/rifle/idle/survivor-idle_rifle_5.png";
    render["soldier-rifle-idle-6"] = "../content/player/rifle/idle/survivor-idle_rifle_6.png";
    render["soldier-rifle-idle-7"] = "../content/player/rifle/idle/survivor-idle_rifle_7.png";
    render["soldier-rifle-idle-8"] = "../content/player/rifle/idle/survivor-idle_rifle_8.png";
    render["soldier-rifle-idle-9"] = "../content/player/rifle/idle/survivor-idle_rifle_9.png";
    render["soldier-rifle-idle-10"] = "../content/player/rifle/idle/survivor-idle_rifle_10.png";
    render["soldier-rifle-idle-11"] = "../content/player/rifle/idle/survivor-idle_rifle_11.png";
    render["soldier-rifle-idle-12"] = "../content/player/rifle/idle/survivor-idle_rifle_12.png";
    render["soldier-rifle-idle-13"] = "../content/player/rifle/idle/survivor-idle_rifle_13.png";
    render["soldier-rifle-idle-14"] = "../content/player/rifle/idle/survivor-idle_rifle_14.png";
    render["soldier-rifle-idle-15"] = "../content/player/rifle/idle/survivor-idle_rifle_15.png";
    render["soldier-rifle-idle-16"] = "../content/player/rifle/idle/survivor-idle_rifle_16.png";
    render["soldier-rifle-idle-17"] = "../content/player/rifle/idle/survivor-idle_rifle_17.png";
    render["soldier-rifle-idle-18"] = "../content/player/rifle/idle/survivor-idle_rifle_18.png";
    render["soldier-rifle-idle-19"] = "../content/player/rifle/idle/survivor-idle_rifle_19.png";
    render["soldier-rifle-shoot-0"] = "../content/player/rifle/shoot/survivor-shoot_rifle_0.png";
    render["soldier-rifle-shoot-1"] = "../content/player/rifle/shoot/survivor-shoot_rifle_1.png";
    render["soldier-rifle-shoot-2"] = "../content/player/rifle/shoot/survivor-shoot_rifle_2.png";
    render["soldier-rifle-reload-0"] = "../content/player/rifle/reload/survivor-reload_rifle_0.png";
    render["soldier-rifle-reload-1"] = "../content/player/rifle/reload/survivor-reload_rifle_1.png";
    render["soldier-rifle-reload-2"] = "../content/player/rifle/reload/survivor-reload_rifle_2.png";
    render["soldier-rifle-reload-3"] = "../content/player/rifle/reload/survivor-reload_rifle_3.png";
    render["soldier-rifle-reload-4"] = "../content/player/rifle/reload/survivor-reload_rifle_4.png";
    render["soldier-rifle-reload-5"] = "../content/player/rifle/reload/survivor-reload_rifle_5.png";
    render["soldier-rifle-reload-6"] = "../content/player/rifle/reload/survivor-reload_rifle_6.png";
    render["soldier-rifle-reload-7"] = "../content/player/rifle/reload/survivor-reload_rifle_7.png";
    render["soldier-rifle-reload-8"] = "../content/player/rifle/reload/survivor-reload_rifle_8.png";
    render["soldier-rifle-reload-9"] = "../content/player/rifle/reload/survivor-reload_rifle_9.png";
    render["soldier-rifle-reload-10"] = "../content/player/rifle/reload/survivor-reload_rifle_10.png";
    render["soldier-rifle-reload-11"] = "../content/player/rifle/reload/survivor-reload_rifle_11.png";
    render["soldier-rifle-reload-12"] = "../content/player/rifle/reload/survivor-reload_rifle_12.png";
    render["soldier-rifle-reload-13"] = "../content/player/rifle/reload/survivor-reload_rifle_13.png";
    render["soldier-rifle-reload-14"] = "../content/player/rifle/reload/survivor-reload_rifle_14.png";
    render["soldier-rifle-reload-15"] = "../content/player/rifle/reload/survivor-reload_rifle_15.png";
    render["soldier-rifle-reload-16"] = "../content/player/rifle/reload/survivor-reload_rifle_16.png";
    render["soldier-rifle-reload-17"] = "../content/player/rifle/reload/survivor-reload_rifle_17.png";
    render["soldier-rifle-reload-18"] = "../content/player/rifle/reload/survivor-reload_rifle_18.png";
    render["soldier-rifle-reload-19"] = "../content/player/rifle/reload/survivor-reload_rifle_19.png";
    render["soldier-handgun-idle-0"] = "../content/player/handgun/idle/survivor-idle_handgun_0.png";
    render["soldier-handgun-idle-1"] = "../content/player/handgun/idle/survivor-idle_handgun_1.png";
    render["soldier-handgun-idle-2"] = "../content/player/handgun/idle/survivor-idle_handgun_2.png";
    render["soldier-handgun-idle-3"] = "../content/player/handgun/idle/survivor-idle_handgun_3.png";
    render["soldier-handgun-idle-4"] = "../content/player/handgun/idle/survivor-idle_handgun_4.png";
    render["soldier-handgun-idle-5"] = "../content/player/handgun/idle/survivor-idle_handgun_5.png";
    render["soldier-handgun-idle-6"] = "../content/player/handgun/idle/survivor-idle_handgun_6.png";
    render["soldier-handgun-idle-7"] = "../content/player/handgun/idle/survivor-idle_handgun_7.png";
    render["soldier-handgun-idle-8"] = "../content/player/handgun/idle/survivor-idle_handgun_8.png";
    render["soldier-handgun-idle-9"] = "../content/player/handgun/idle/survivor-idle_handgun_9.png";
    render["soldier-handgun-idle-10"] = "../content/player/handgun/idle/survivor-idle_handgun_10.png";
    render["soldier-handgun-idle-11"] = "../content/player/handgun/idle/survivor-idle_handgun_11.png";
    render["soldier-handgun-idle-12"] = "../content/player/handgun/idle/survivor-idle_handgun_12.png";
    render["soldier-handgun-idle-13"] = "../content/player/handgun/idle/survivor-idle_handgun_13.png";
    render["soldier-handgun-idle-14"] = "../content/player/handgun/idle/survivor-idle_handgun_14.png";
    render["soldier-handgun-idle-15"] = "../content/player/handgun/idle/survivor-idle_handgun_15.png";
    render["soldier-handgun-idle-16"] = "../content/player/handgun/idle/survivor-idle_handgun_16.png";
    render["soldier-handgun-idle-17"] = "../content/player/handgun/idle/survivor-idle_handgun_17.png";
    render["soldier-handgun-idle-18"] = "../content/player/handgun/idle/survivor-idle_handgun_18.png";
    render["soldier-handgun-idle-19"] = "../content/player/handgun/idle/survivor-idle_handgun_19.png";
    render["soldier-handgun-shoot-0"] = "../content/player/handgun/shoot/survivor-shoot_handgun_0.png";
    render["soldier-handgun-shoot-1"] = "../content/player/handgun/shoot/survivor-shoot_handgun_1.png";
    render["soldier-handgun-shoot-2"] = "../content/player/handgun/shoot/survivor-shoot_handgun_2.png";
    render["soldier-handgun-reload-0"] = "../content/player/handgun/reload/survivor-reload_handgun_0.png";
    render["soldier-handgun-reload-1"] = "../content/player/handgun/reload/survivor-reload_handgun_1.png";
    render["soldier-handgun-reload-2"] = "../content/player/handgun/reload/survivor-reload_handgun_2.png";
    render["soldier-handgun-reload-3"] = "../content/player/handgun/reload/survivor-reload_handgun_3.png";
    render["soldier-handgun-reload-4"] = "../content/player/handgun/reload/survivor-reload_handgun_4.png";
    render["soldier-handgun-reload-5"] = "../content/player/handgun/reload/survivor-reload_handgun_5.png";
    render["soldier-handgun-reload-6"] = "../content/player/handgun/reload/survivor-reload_handgun_6.png";
    render["soldier-handgun-reload-7"] = "../content/player/handgun/reload/survivor-reload_handgun_7.png";
    render["soldier-handgun-reload-8"] = "../content/player/handgun/reload/survivor-reload_handgun_8.png";
    render["soldier-handgun-reload-9"] = "../content/player/handgun/reload/survivor-reload_handgun_9.png";
    render["soldier-handgun-reload-10"] = "../content/player/handgun/reload/survivor-reload_handgun_10.png";
    render["soldier-handgun-reload-11"] = "../content/player/handgun/reload/survivor-reload_handgun_11.png";
    render["soldier-handgun-reload-12"] = "../content/player/handgun/reload/survivor-reload_handgun_12.png";
    render["soldier-handgun-reload-13"] = "../content/player/handgun/reload/survivor-reload_handgun_13.png";
    render["soldier-handgun-reload-14"] = "../content/player/handgun/reload/survivor-reload_handgun_14.png";
    render["soldier-handgun-reload-15"] = "../content/player/handgun/reload/survivor-reload_handgun_15.png";
    render["soldier-handgun-reload-16"] = "../content/player/handgun/reload/survivor-reload_handgun_16.png";
    render["soldier-handgun-reload-17"] = "../content/player/handgun/reload/survivor-reload_handgun_17.png";
    render["soldier-handgun-reload-18"] = "../content/player/handgun/reload/survivor-reload_handgun_18.png";
    render["soldier-handgun-reload-19"] = "../content/player/handgun/reload/survivor-reload_handgun_19.png";
    render["soldier-shotgun-idle-0"] = "../content/player/shotgun/idle/survivor-idle_shotgun_0.png";
    render["soldier-shotgun-idle-1"] = "../content/player/shotgun/idle/survivor-idle_shotgun_1.png";
    render["soldier-shotgun-idle-2"] = "../content/player/shotgun/idle/survivor-idle_shotgun_2.png";
    render["soldier-shotgun-idle-3"] = "../content/player/shotgun/idle/survivor-idle_shotgun_3.png";
    render["soldier-shotgun-idle-4"] = "../content/player/shotgun/idle/survivor-idle_shotgun_4.png";
    render["soldier-shotgun-idle-5"] = "../content/player/shotgun/idle/survivor-idle_shotgun_5.png";
    render["soldier-shotgun-idle-6"] = "../content/player/shotgun/idle/survivor-idle_shotgun_6.png";
    render["soldier-shotgun-idle-7"] = "../content/player/shotgun/idle/survivor-idle_shotgun_7.png";
    render["soldier-shotgun-idle-8"] = "../content/player/shotgun/idle/survivor-idle_shotgun_8.png";
    render["soldier-shotgun-idle-9"] = "../content/player/shotgun/idle/survivor-idle_shotgun_9.png";
    render["soldier-shotgun-idle-10"] = "../content/player/shotgun/idle/survivor-idle_shotgun_10.png";
    render["soldier-shotgun-idle-11"] = "../content/player/shotgun/idle/survivor-idle_shotgun_11.png";
    render["soldier-shotgun-idle-12"] = "../content/player/shotgun/idle/survivor-idle_shotgun_12.png";
    render["soldier-shotgun-idle-13"] = "../content/player/shotgun/idle/survivor-idle_shotgun_13.png";
    render["soldier-shotgun-idle-14"] = "../content/player/shotgun/idle/survivor-idle_shotgun_14.png";
    render["soldier-shotgun-idle-15"] = "../content/player/shotgun/idle/survivor-idle_shotgun_15.png";
    render["soldier-shotgun-idle-16"] = "../content/player/shotgun/idle/survivor-idle_shotgun_16.png";
    render["soldier-shotgun-idle-17"] = "../content/player/shotgun/idle/survivor-idle_shotgun_17.png";
    render["soldier-shotgun-idle-18"] = "../content/player/shotgun/idle/survivor-idle_shotgun_18.png";
    render["soldier-shotgun-idle-19"] = "../content/player/shotgun/idle/survivor-idle_shotgun_19.png";
    render["soldier-shotgun-shoot-0"] = "../content/player/shotgun/shoot/survivor-shoot_shotgun_0.png";
    render["soldier-shotgun-shoot-1"] = "../content/player/shotgun/shoot/survivor-shoot_shotgun_1.png";
    render["soldier-shotgun-shoot-2"] = "../content/player/shotgun/shoot/survivor-shoot_shotgun_2.png";
    render["soldier-shotgun-reload-0"] = "../content/player/shotgun/reload/survivor-reload_shotgun_0.png";
    render["soldier-shotgun-reload-1"] = "../content/player/shotgun/reload/survivor-reload_shotgun_1.png";
    render["soldier-shotgun-reload-2"] = "../content/player/shotgun/reload/survivor-reload_shotgun_2.png";
    render["soldier-shotgun-reload-3"] = "../content/player/shotgun/reload/survivor-reload_shotgun_3.png";
    render["soldier-shotgun-reload-4"] = "../content/player/shotgun/reload/survivor-reload_shotgun_4.png";
    render["soldier-shotgun-reload-5"] = "../content/player/shotgun/reload/survivor-reload_shotgun_5.png";
    render["soldier-shotgun-reload-6"] = "../content/player/shotgun/reload/survivor-reload_shotgun_6.png";
    render["soldier-shotgun-reload-7"] = "../content/player/shotgun/reload/survivor-reload_shotgun_7.png";
    render["soldier-shotgun-reload-8"] = "../content/player/shotgun/reload/survivor-reload_shotgun_8.png";
    render["soldier-shotgun-reload-9"] = "../content/player/shotgun/reload/survivor-reload_shotgun_9.png";
    render["soldier-shotgun-reload-10"] = "../content/player/shotgun/reload/survivor-reload_shotgun_10.png";
    render["soldier-shotgun-reload-11"] = "../content/player/shotgun/reload/survivor-reload_shotgun_11.png";
    render["soldier-shotgun-reload-12"] = "../content/player/shotgun/reload/survivor-reload_shotgun_12.png";
    render["soldier-shotgun-reload-13"] = "../content/player/shotgun/reload/survivor-reload_shotgun_13.png";
    render["soldier-shotgun-reload-14"] = "../content/player/shotgun/reload/survivor-reload_shotgun_14.png";
    render["soldier-shotgun-reload-15"] = "../content/player/shotgun/reload/survivor-reload_shotgun_15.png";
    render["soldier-shotgun-reload-16"] = "../content/player/shotgun/reload/survivor-reload_shotgun_16.png";
    render["soldier-shotgun-reload-17"] = "../content/player/shotgun/reload/survivor-reload_shotgun_17.png";
    render["soldier-shotgun-reload-18"] = "../content/player/shotgun/reload/survivor-reload_shotgun_18.png";
    render["soldier-shotgun-reload-19"] = "../content/player/shotgun/reload/survivor-reload_shotgun_19.png";
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


TTF_Font *AssetManager::loadFont(string fontToken, const int size) {
    TTF_Font *font = TTF_OpenFont(fonts[fontToken], size);
    if (font == NULL)
        cout << "Unable to load font %s! SDL_image Error: " << render[fontToken] << TTF_GetError() << endl;

    return font;
}

SDL_Texture *AssetManager::loadTexture(string mediaToken) {
    SDL_Surface *surface = loadSurface(mediaToken);
    if (!surface)
        cout << SDL_GetError() << endl;
    SDL_Texture *texture = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);


    if (texture == NULL) {
        printf(SDL_GetError());
    }
    return texture;
}
