#include "TickerTime.h"
#include <SDL.h>
#include <algorithm>

TickerTime::TickerTime(const unsigned fps, const unsigned maxFps) : _fps{ fps }, _maxFps{maxFps}, _minimumFrameTime{ fps / 1000.0f }, _lastUpdateTime {SDL_GetTicks()}
{
}

TickerTime::~TickerTime()
{
}

// Delta time in seconds
float TickerTime::GetDeltaTime()
{
	const int currentTimeMs = SDL_GetTicks();
	const auto frameTime = currentTimeMs - _lastUpdateTime;
	const auto time = std::min<unsigned>(frameTime, _maxFps);

	_lastUpdateTime = time;

	return time / 1000.0f;
}

void TickerTime:: WaitNextUpdate() const
{
	// Check how long the frame took and wait for the next frame if it updated 'too' fast.
	// results in fixed fps
	if ((SDL_GetTicks() - _lastUpdateTime) < _minimumFrameTime)
		SDL_Delay(_minimumFrameTime - (SDL_GetTicks() - _lastUpdateTime));
}