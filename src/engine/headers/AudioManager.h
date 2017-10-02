#pragma once

#include <SDL.h>
#include <iostream>
#include "SDL_mixer.h"
#include "AssetManager.h"

using namespace std;

class AudioManager {

public:
	AudioManager();
	int initMusicPlayer();
	static AudioManager* instance();
	int loadBGM(string audioToken);
	void playBGM();
	void pauseResumeBGM();
	void stopBGM();
	int playEffect(string audioToken);
	void close();
private:
	static AudioManager* sInstance;
	Mix_Music* gBGM;
	Mix_Chunk* gEffectM;
};