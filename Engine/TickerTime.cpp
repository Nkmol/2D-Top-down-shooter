#include "TickerTime.h"
#include <SDL.h>
#include <functional>

TickerTime::TickerTime(const unsigned targetFps, const unsigned maxFps) : _targetFps{targetFps}, _maxFps{maxFps},
                                                                          _lastUpdateTime{SDL_GetPerformanceCounter()},
                                                                          _ticksPerSecond {
	                                                                          SDL_GetPerformanceFrequency()
                                                                          },
                                                                          _targetTicksPerFrame {
	                                                                          _ticksPerSecond / _targetFps
                                                                          }, _accumulator {0.0}, _timesRendered{0}
{
}

// Happens when the loop catches up (when lagging)
void TickerTime::OnCatchUp(const DelegateFunction func)
{
	_catchUpFunctions.push_back(func);
}

// Happens every frame
void TickerTime::OnFrame(const DelegateFunction func)
{
	_frameFunctions.push_back(func);
}

// Happens every x seconds
void TickerTime::PerSecond(const int secondInterval, DelegateFunction func)
{
	
}

float TickerTime::GetDeltaTime() const
{
	return _targetTicksPerFrame / static_cast<float>(_ticksPerSecond);
}

void TickerTime::Run(const bool& exitWhen)
{
	while(exitWhen)
	{
		const auto time = SDL_GetPerformanceCounter();
		const auto deltaTime = time - _lastUpdateTime;
		_lastUpdateTime = time;

		_accumulator += deltaTime;

		// update game logic as lag permits -> physics catch up
		while (_accumulator >= _targetTicksPerFrame)
		{
			// TODO: Split physics and non-physic logic with 2 different updates
			// update at a fixed rate each time
			//Update(targetTicksPerFrame / static_cast<float>(ticksPerSecond)); // ticks to seconds

			for (auto && catchUpFunction : _catchUpFunctions)
			{
				catchUpFunction();
			}
			_accumulator -= _targetTicksPerFrame;
		}

		// Draw only once per sec
	/*	if (t % targetFps == 0)
		{
			_fps = static_cast<float>(ticksPerSecond) / deltaTime;
		}*/

		for (auto && frameFunction : _frameFunctions)
		{
			frameFunction();
		}
	}
}

TickerTime::~TickerTime()
{
}
