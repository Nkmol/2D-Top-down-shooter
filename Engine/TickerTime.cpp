#include "TickerTime.h"
#include <SDL.h>
#include <algorithm>

TickerTime::TickerTime(const unsigned fps, const unsigned maxFps) : _fps{fps}, _maxFps{maxFps},
                                                                    _lastUpdateTime(SDL_GetPerformanceCounter())
{
}

TickerTime::~TickerTime()
{
}

// Delta time in seconds
float TickerTime::GetDeltaTime()
{
	const int currentTimeMs = SDL_GetPerformanceCounter();
	const auto elapsedTime = currentTimeMs - _lastUpdateTime;
	const auto time = std::min<unsigned>(elapsedTime, _maxFps);

	_lastUpdateTime = currentTimeMs;

	return (time * 1000.0f) / SDL_GetPerformanceFrequency();
}
