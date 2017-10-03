#pragma once

#include <SDL.h>
#include <iostream>
#include "SDL_mixer.h"
#include "AssetManager.h"
class AudioManager {

public:
	AudioManager();
	int initMusicPlayer();
	static AudioManager* instance();
	int loadBGM(std::string audioToken);
	void playBGM();
	void pauseResumeBGM();
	void stopBGM();
	int playEffect(std::string audioToken);
	void close();
private:
	static AudioManager* sInstance;
	Mix_Music* gBGM;
	Mix_Chunk* gEffectM;
};