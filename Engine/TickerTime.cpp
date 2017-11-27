#include "TickerTime.h"

TickerTime::TickerTime(const unsigned targetFps, const unsigned maxFps) : _targetFps{targetFps}, _maxFps{maxFps},
                                                                          _lastUpdateTime{SDL_GetPerformanceCounter()},
                                                                          _lastDeltaTime(0),
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

int TickerTime::GetFps() const
{
	/*std::cout << _ticksPerSecond << " / " << _lastDeltaTime << " = " << (static_cast<float>(_ticksPerSecond) / (
		_lastDeltaTime)) << std::endl;*/
	return static_cast<float>(_ticksPerSecond) / _lastDeltaTime;
}

void TickerTime::Run(const bool& exitWhen)
{
	while (exitWhen)
	{
		const auto time = SDL_GetPerformanceCounter();
		_lastDeltaTime = time - _lastUpdateTime;
		_lastUpdateTime = time;

		_accumulator += _lastDeltaTime;

		// update game logic as lag permits -> physics catch up
		while (_accumulator >= _targetTicksPerFrame)
		{
			for (auto&& catchUpFunction : _catchUpFunctions)
			{
				catchUpFunction();
			}
			_accumulator -= _targetTicksPerFrame;
		}

		// For every second
		if (_timesRendered % _targetFps == 0)
		{
			for (auto&& onSecondFunction : _onSecondFunctions)
			{
				onSecondFunction.Tick();
			}
		}

		for (auto&& frameFunction : _frameFunctions)
		{
			frameFunction();
		}

		_timesRendered += 1;
	}
}

TickerTime::~TickerTime()
{
}
