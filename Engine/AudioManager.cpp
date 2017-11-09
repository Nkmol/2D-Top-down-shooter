#include "AudioManager.h"

//how to call: AudioManager::instance()->playBGM();
AudioManager& AudioManager::Instance()
{
	// TODO to refernece, can never be nullptr (should never)
	static AudioManager sInstance; // Guaranteed to be destroyed.
									// Instantiated on first use.

	return sInstance;
}

AudioManager::AudioManager()
{
	gBGM = nullptr;
	gEffectM = nullptr;
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
	gBGM = AssetManager::getInstance().loadBGM(audioToken);
	if (gBGM == NULL)
	{
		cout << "Failed to load beat music! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
		return 1;
	}
	return 0;
}


int AudioManager::PlayEffect(string audioToken)
{
	//Mix_Chunk* effectM = Mix_LoadWAV(name);
	gEffectM = AssetManager::getInstance().loadEffect(audioToken);
	if (gEffectM == NULL)
	{
		cout << "Failed to load scratch sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
		return 1;
	}
	Mix_PlayChannel(-1, gEffectM, 0);
	return 0;
}

void AudioManager::PlayBGM()
{
	cout << "playing music: " << endl;

	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(gBGM, -1);
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
		PlayBGM();
	}
}

void AudioManager::StopBGM()
{
	Mix_HaltMusic();
}

void AudioManager::Close()
{
	//Free the music
	Mix_FreeMusic(gBGM);
	gBGM = NULL;

	//Quit SDL subsystems
	Mix_Quit();
}