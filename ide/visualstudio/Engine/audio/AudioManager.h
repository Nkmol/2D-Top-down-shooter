#pragma once

#include <SDL.h>
#include "../SDL_mixer.h"
#include <iostream>
//#include "AssetManager.h>

using namespace std;

class AudioManager {

public:
	AudioManager();
	int initMusicPlayer();
	static AudioManager* instance();
	int loadBGM(const char* name);
	void playBGM();
	void pauseResumeBGM();
	void stopBGM();
	int playEffect(const char* name);
	void close();
private:
	static AudioManager* sInstance;
	Mix_Music* gBGM;
};