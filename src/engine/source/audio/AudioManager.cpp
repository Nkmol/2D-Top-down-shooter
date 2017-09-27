#include "AudioManager.h"

//how to call: AudioManager::instance()->playBGM();
AudioManager* AudioManager::instance()
{
	if (!sInstance) {
		static AudioManager sInstance;
		sInstance.initMusicPlayer();
	}
	return sInstance;
}

AudioManager::AudioManager()
{
	gBGM = nullptr;
}

int AudioManager::initMusicPlayer()
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

int AudioManager::loadBGM(const char* name)
{
	//Load music
	gBGM = Mix_LoadMUS(name);
	//gBGM = AssetManager.getInstance()->getMixMusic(name);
	if (gBGM == NULL)
	{
		cout << "Failed to load beat music! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
		return 1;
	}
	return 0;
}


int AudioManager::playEffect(const char* name)
{
	Mix_Chunk* effectM = Mix_LoadWAV(name);
	//gEffectM = AssetManager.getInstance()->getMixChunk(name);
	if (gEffectM == NULL)
	{
		cout << "Failed to load scratch sound effect! SDL_mixer Error: %s\n" << Mix_GetError() << endl;
		return 1;
	}
	Mix_PlayChannel(-1, gEffectM, 0);
	return 0;
}

void AudioManager::playBGM()
{
	cout << "playing music: " << endl;

	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(gBGM, -1);
	}
}

void AudioManager::pauseResumeBGM()
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
		playBGM();
	}
}

void AudioManager::stopBGM()
{
	Mix_HaltMusic();
}

void AudioManager::close()
{
	//Free the music
	Mix_FreeMusic(gBGM);
	gBGM = NULL;
	
	//Quit SDL subsystems
	Mix_Quit();
}
