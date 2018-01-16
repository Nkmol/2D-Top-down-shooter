#include "TickerTime.h"
#include <ostream>
#include <iostream>
#include <thread>

TickerTime::TickerTime(const unsigned targetFps, const unsigned maxFps) : _targetFps{targetFps}, _maxFps{maxFps},
                                                                          _startPreviousFrame{SDL_GetPerformanceCounter()},
                                                                          _lastDeltaTicks(0),
                                                                          _ticksPerSecond { SDL_GetPerformanceFrequency() },
                                                                          _targetTicksPerFrame { _ticksPerSecond / _targetFps}, 
																		  _accumulator {0.0}, 
																		  _timesRendered{0}
{
}

// Happens when the loop catches up (when lagging)
void TickerTime::OnCatchUp(const DelegateFunction&&  func)
{
	_catchUpFunctions.push_back(std::move(func));
}

// Happens every frame
void TickerTime::OnFrame(const DelegateFunction&&  func)
{
	_frameFunctions.push_back(std::move(func));
}

// Happens every x seconds
void TickerTime::PerSecond(const int secondInterval, DelegateFunction&& func)
{
	_onSecondFunctions.emplace_back(secondInterval, std::move(func));
}

// The actual multiplier of the game time, representing 1 tick in 1 second
float TickerTime::GetGameTime() const
{
	return _targetTicksPerFrame / static_cast<float>(_ticksPerSecond);
}

double TickerTime::GetMsOfCurrentFrame() const
{
	return (SDL_GetPerformanceCounter() - _startPreviousFrame) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency());
}

double TickerTime::GetFps() const
{
	/*std::cout << SDL_GetPerformanceFrequency() << " / " << _lastDeltaTicks << " = " << (static_cast<float>(_ticksPerSecond) / (
		_lastDeltaTicks)) << std::endl;*/

	// 1 seconds / ms in one frame
	return 1000.0 / GetMsOfCurrentFrame();
}

void TickerTime::Run(const bool& exitWhen)
{
	// For second events
	float actualTimeRun = 0;
	auto lastTimeRun = 0;

	while (exitWhen)
	{
		const auto ticksNow = SDL_GetPerformanceCounter();
		_lastDeltaTicks = ticksNow - _startPreviousFrame;

		_accumulator += _lastDeltaTicks;
		// update game logic as lag permits -> physics catch up
		while (_accumulator >= _targetTicksPerFrame)
		{
			for (const auto& catchUpFunction : _catchUpFunctions)
			{
				catchUpFunction();
			}
			_accumulator -= _targetTicksPerFrame;

			// Check after first accumalotr resolve if still lagg
			if (_accumulator >= _targetTicksPerFrame) {
//				SDL_Log("Current lag is %f ms", _accumulator * 1000 / static_cast<double>(SDL_GetPerformanceFrequency()));

				// Skip catching up when it falls to far behind (5 frames behind for now)
				if (_accumulator >= _targetTicksPerFrame * 5)
				{
//					SDL_LogCritical(2, "Skipping frames, falls too far behind");
					_accumulator = 0;
				}
			}
		}

		// For every second
		if (lastTimeRun < static_cast<int>(actualTimeRun))
		{
			lastTimeRun = actualTimeRun;
			for (auto& onSecondFunction : _onSecondFunctions)
			{
				onSecondFunction.Tick();
			}

			//SDL_Log("Timeframe took %f ms based on previous frame", GetMsOfCurrentFrame());
		}

		for (const auto& frameFunction : _frameFunctions)
		{
			frameFunction();
		}


		actualTimeRun += GetMsOfCurrentFrame() / 1000;
		_timesRendered += 1;

		//auto start = SDL_GetPerformanceCounter();
		//SDL_Log("update   took %f ms", (double)((start - ticksNow) * 1000) / SDL_GetPerformanceFrequency());

		// Wait for next frame (caps frames)
		long delay = 1000.0l / _maxFps - (SDL_GetPerformanceCounter() - ticksNow) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency());
		if (delay > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}

		_startPreviousFrame = ticksNow;

		//auto s1 = SDL_GetPerformanceCounter();
		//SDL_Log("timefame took %f ms with function result of %f ms", (double)((s1 - ticksNow) * 1000) / SDL_GetPerformanceFrequency(), GetMsOfCurrentFrame());
		//SDL_Log("delay took    %f ms with a delay of %f ms", (double)((s1 - start) * 1000) / SDL_GetPerformanceFrequency(), (double)(std::chrono::milliseconds(delay).count()));

	}
}

TickerTime::~TickerTime()
{
}
