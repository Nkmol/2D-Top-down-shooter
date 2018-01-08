#pragma once

#include "SDL_mixer.h"
#include "AssetManager.h"

using namespace std;

class AudioManager {

public:
	AudioManager(AudioManager const&) = delete;
	void operator=(AudioManager const&) = delete;

	int InitMusicPlayer();
	static AudioManager& Instance();
	int LoadBGM(string audioToken);
	void PlayBGM();
	void PauseResumeBGM();
	void StopBGM();
	int PlayEffect(string audioToken);
	void Close();
private:
	AudioManager();

	static AudioManager* _instance;
	Mix_Music* _bgm;
	Mix_Chunk* _effectMusic;
};