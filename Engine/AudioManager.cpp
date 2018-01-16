#include "AudioManager.h"

//how to call: AudioManager::instance()->playBGM();
AudioManager& AudioManager::Instance()
{
	// TODO to refernece, can never be nullptr (should never)
	static AudioManager _instance; // Guaranteed to be destroyed.
									// Instantiated on first use.

	return _instance;
}

AudioManager::AudioManager()
{
	_bgm = nullptr;
	_effectMusic = nullptr;
}

int AudioManager::InitMusicPlayer()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_AUDIO) < 0)
	{
		cout << "SDL could not initialize! SDL Error: %s\n" << SDL_GetError() << endl;
		return 1;
	}

	//Initialize SDL_mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		cout << "SDL_mixer could not initialize! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
		return 1;
	}

	return 0;
}

int AudioManager::LoadBGM(string audioToken)
{
	//Load music
	//gBGM = Mix_LoadMUS(name);
	if (Mix_PlayingMusic() == 1){
		StopBGM();
		Mix_FreeMusic(_bgm);
	}
	_bgm = AssetManager::Instance().LoadBGM(audioToken);
	if (_bgm == NULL)
	{
		cout << "Failed to load beat music! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
		return 1;
	}
	return 0;
}


int AudioManager::PlayEffect(string audioToken)
{
	Mix_FreeChunk(_effectMusic);
	//Mix_Chunk* effectM = Mix_LoadWAV(name);
	_effectMusic = AssetManager::Instance().LoadEffect(audioToken);
	Mix_VolumeChunk(_effectMusic, MIX_MAX_VOLUME/8);
	if (_effectMusic == NULL)
	{
		cout << "Failed to load scratch sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
		return 1;
	}
	Mix_PlayChannel(-1, _effectMusic, 0);
	return 0;
}

	// -1 is infinite
void AudioManager::PlayBGM(int loops = -1)
{
	Mix_VolumeMusic(MIX_MAX_VOLUME / 8);

	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(_bgm, -1);
	}
}

void AudioManager::PauseResumeBGM()
{
	if (Mix_PlayingMusic() == 1)
	{
		//If the music is paused
		if (Mix_PausedMusic() == 1)
		{
			//Resume the music
			Mix_ResumeMusic();
		}
		//If the music is playing
		else
		{
			//Pause the music
			Mix_PauseMusic();
		}
	}
	else {
		PlayBGM(-1);
	}
}

void AudioManager::StopBGM()
{
	Mix_HaltMusic();
}

void AudioManager::Close()
{
	//Free the music
	Mix_FreeMusic(_bgm);
	Mix_FreeChunk(_effectMusic);
	_bgm = NULL;

	//Quit SDL subsystems
	Mix_Quit();
}