#pragma once
#include <iostream>
#include <vector>
#include "json.hpp"

struct FlockVars
{
public:
	int type;
	int amount;
	int minPos;
	int maxPos;

	static void from_json(const nlohmann::json& j, FlockVars& value);
};
class Wave
{
	int _id;
	float _time;
	float _multiplier;
	std::vector<FlockVars> _flocksVars;

public:
	const int GetId() const { return _id; }
	void SetId(const int id) { _id = id; }
	const float GetTime() const { return _time; }
	void SetTime(const float time) { _time = time; }
	const float GetMultiplier() const { return _multiplier; }
	void SetMultiplier(const float multiplier) { _multiplier = multiplier; }
	void SetFlocksVars(const std::vector<FlockVars> vars) { _flocksVars = vars; }
	const std::vector<FlockVars> GetFlocksVars() const { return _flocksVars; }
};

void from_json(const nlohmann::json& j, Wave& value);
