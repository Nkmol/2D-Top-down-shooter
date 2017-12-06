#pragma once
#include <iostream>
#include <vector>
#include <json.hpp>
using json = nlohmann::json;

struct FlockVars
{
	std::string type;
	int amount;
	int minPos;
	int maxPos;

	static void from_json(const json& j, FlockVars& value);
};
class Wave
{
	int _id;
	float _time;
	float _multiplier;
	std::vector<FlockVars> _flocksVars;

public:
	const int get_id() const { return _id; }
	void set_id(const int id) { _id = id; }
	const float get_time() const { return _time; }
	void set_time(const float time) { _time = time; }
	const float get_multiplier() const { return _multiplier; }
	void set_multiplier(const float multiplier) { _multiplier = multiplier; }
	void set_flocksvars(const std::vector<FlockVars> vars) { _flocksVars = vars; }
};

void from_json(const json& j, Wave& value);
