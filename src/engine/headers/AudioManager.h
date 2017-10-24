#pragma once

#include <SDL.h>
#include <iostream>
#include "SDL_mixer.h"
#include "AssetManager.h"

using namespace std;

class AudioManager {

public:
	AudioManager();
	int InitMusicPlayer();
	static AudioManager* Instance();
	int LoadBGM(string audioToken);
	void PlayBGM();
	void PauseResumeBGM();
	void StopBGM();
	int PlayEffect(string audioToken);
	void Close();
private:
	static AudioManager* sInstance;
	Mix_Music* gBGM;
	Mix_Chunk* gEffectM;
};