#pragma once
#include <SDL_hints.h>
#include <functional>
#include <memory>
#include <vector>
#include <map>

class TickerTime
{
	unsigned _targetFps;
	unsigned _maxFps;

	Uint64 _lastUpdateTime;
	Uint64 _ticksPerSecond;
	Uint64 _targetTicksPerFrame;
	double _accumulator;
	int _timesRendered;

	typedef std::function<void()> DelegateFunction;

	std::vector<DelegateFunction> _catchUpFunctions;
	std::vector<DelegateFunction> _frameFunctions;
	std::map<int, DelegateFunction> _onSecondFunctions;
public:
	TickerTime(const unsigned fps, const unsigned maxFps);
	void OnCatchUp(const DelegateFunction func);
	void OnFrame(const DelegateFunction func);
	void PerSecond(const int secondInterval, DelegateFunction func);
	float GetDeltaTime() const;
	void Run(const bool& exitWhen);
	~TickerTime();
};

