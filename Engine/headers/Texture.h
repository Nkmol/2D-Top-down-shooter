#pragma once
#include <SDL.h>
#include "RenderManager.h"

class Texture
{
	SDL_Texture* _texture;

public:
	Texture(SDL_Surface* surface)
	{
		_texture = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface);
	}

	Texture(SDL_Texture* texture)
	{
		_texture = texture;
	}

	Texture(std::string token)
	{
		_texture = SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), AssetManager::Instance().LoadSurface(token));
	}

	~Texture()
	{
		SDL_DestroyTexture(_texture);
	}

	SDL_Texture* GetTexture()
	{
		return _texture;
	}
};