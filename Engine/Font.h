#pragma once
#include <SDL_ttf.h>
#include "SdlWrapper.h"

class Font : public SdlWrapper<TTF_Font>
{
	using SdlWrapper<TTF_Font>::SdlWrapper;
};
