#pragma once
#include <functional>
#include <vector>
#include <SDL.h>
#include <functional>

class TickerTime
{
	typedef std::function<void()> DelegateFunction;

public:
	struct CountdownEvent
	{
	private:
		int _time;
		int _currentTime;
		DelegateFunction _func;
	public:
		CountdownEvent(const int time, const DelegateFunction func) : _time{time}, _currentTime{time}, _func{func}
		{
		}

		void Tick()
		{
			_currentTime -= 1;
			if (_currentTime <= 0)
			{
				_func();

				// reset
				_currentTime = _time;
			}
		}
	};

private:
	unsigned _targetFps;
	unsigned _maxFps;

	Uint64 _startPreviousFrame;
	Uint64 _lastDeltaTicks;
	Uint64 _ticksPerSecond;
	Uint64 _targetTicksPerFrame;
	double _accumulator;
	int _timesRendered;


	std::vector<DelegateFunction> _catchUpFunctions;
	std::vector<DelegateFunction> _frameFunctions;
	std::vector<CountdownEvent> _onSecondFunctions;

	double GetMsOfCurrentFrame() const;
public:
	TickerTime(const unsigned fps, const unsigned maxFps);
	void OnCatchUp(const DelegateFunction&& func);
	void OnFrame(const DelegateFunction&& func);
	void PerSecond(const int secondInterval, DelegateFunction&& func);
	float GetGameTime() const;
	double GetFps() const;
	void Run(const bool& exitWhen);
	~TickerTime();
};

