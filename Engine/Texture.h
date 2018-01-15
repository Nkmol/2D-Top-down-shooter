#pragma once
#include <SDL.h>
#include "RenderManager.h"
#include "AssetManager.h"
#include "SdlWrapper.h"

class Texture : public SdlWrapper<SDL_Texture>
{
public:
	// Only init with Surface
	int width{}, height{};
private:
	// Init size of texture by query
	void InitSize()
	{
		SDL_QueryTexture(GetPointer(), nullptr, nullptr, &width, &height);
	}
public:
	// TODO Not what we actually want
	Texture() : SdlWrapper(nullptr)
	{

	}

	explicit Texture(SDL_Surface* surface) : SdlWrapper(SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), surface))
	{
		width = surface->w;
		height = surface->h;
	}

	explicit Texture(SDL_Texture* texture) : SdlWrapper(texture)
	{
		InitSize();
	}

	explicit Texture(const std::string& token) : SdlWrapper(SDL_CreateTextureFromSurface(RenderManager::Instance().GetRenderer(), AssetManager::Instance().LoadSurface(token)))
	{
		InitSize();
	}
};
