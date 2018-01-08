#pragma once
#include <SDL.h>
#include "RenderManager.h"
#include "AssetManager.h"

class Texture
{
	typedef std::unique_ptr<SDL_Texture, CustomDeleter> TextureType;
	TextureType _texture;

public:
	// Only init with Surface
	int width{}, height{};
	Texture() = default;

	explicit Texture(SDL_Surface* surface)
	{
		width = surface->w;
		height = surface->h;

		const auto& t = RenderManager::Instance().GetRenderer();
		_texture = TextureType(SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface));
		SDL_FreeSurface(surface);
	}

	explicit Texture(SDL_Texture* texture)
	{
		_texture = TextureType(texture);
	}

	explicit Texture(const std::string& token)
	{
		_texture = TextureType(SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), AssetManager::Instance().LoadSurface(token)));
	}

	// TODO: Return the smartptr
	SDL_Texture* GetTexture() const
	{
		return _texture.get();
	}
};