#include "TickerTime.h"

TickerTime::TickerTime(const unsigned targetFps, const unsigned maxFps) : _targetFps{targetFps}, _maxFps{maxFps},
                                                                          _lastUpdateTime{SDL_GetPerformanceCounter()},
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

double TickerTime::GetMsOfLastFrame() const
{
	return _lastDeltaTicks * 1000 / static_cast<double>(SDL_GetPerformanceFrequency());
}

int TickerTime::GetFps() const
{
	/*std::cout << SDL_GetPerformanceFrequency() << " / " << _lastDeltaTicks << " = " << (static_cast<float>(_ticksPerSecond) / (
		_lastDeltaTicks)) << std::endl;*/

	// 1 seconds / ms in one frame
	return 1000 / GetMsOfLastFrame();
}

void TickerTime::Run(const bool& exitWhen)
{
	// For second events
	float actualTimeRun = 0;
	auto lastTimeRun = 0;

	while (exitWhen)
	{
		const auto ticksNow = SDL_GetPerformanceCounter();
		_lastDeltaTicks = ticksNow - _lastUpdateTime;
		_lastUpdateTime = ticksNow;

		_accumulator += _lastDeltaTicks;

		// update game logic as lag permits -> physics catch up
		while (_accumulator >= _targetTicksPerFrame)
		{
			for (const auto& catchUpFunction : _catchUpFunctions)
			{
				catchUpFunction();
			}
			_accumulator -= _targetTicksPerFrame;

		}

		// For every second
		if (lastTimeRun < static_cast<int>(actualTimeRun))
		{
			lastTimeRun = actualTimeRun;
			for (auto& onSecondFunction : _onSecondFunctions)
			{
				onSecondFunction.Tick();
			}
		}

		for (const auto& frameFunction : _frameFunctions)
		{
			frameFunction();
		}


		actualTimeRun += GetMsOfLastFrame() / 1000;
		_timesRendered += 1;

		// Wait for next frame (caps frames)
		long delay = 1000.0l / _maxFps - (SDL_GetPerformanceCounter() - ticksNow) * 1000 / static_cast<double>(SDL_GetPerformanceFrequency());
		if (delay > 0) {
			std::this_thread::sleep_for(std::chrono::milliseconds(delay));
		}
	}
}

TickerTime::~TickerTime()
{
}
