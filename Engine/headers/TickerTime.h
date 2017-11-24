#pragma once
#include <SDL_hints.h>

class TickerTime
{
	unsigned _fps;
	unsigned _maxFps;
	float _minimumFrameTime;

	Uint32 _lastUpdateTime;
public:
	TickerTime(const unsigned fps, const unsigned maxFps);
	~TickerTime();
	float GetDeltaTime();
};

