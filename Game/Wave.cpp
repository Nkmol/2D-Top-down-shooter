#include "Wave.h"


static void from_json(const json& j, FlockVars& value)
{
	value.type = j.at("type").get<std::string>();
	value.amount = j.at("amount").get<int>();
	value.minPos = j.at("minPos").get<int>();
	value.maxPos = j.at("maxPos").get<int>();
}

void from_json(const json& j, Wave& value)
{
	value.set_id(j.at("id").get<int>());
	value.set_time(j.at("time").get<float>());
	value.set_multiplier(j.at("multiplier").get<float>());
	value.set_flocksvars(j.at("flocks").get<std::vector<FlockVars>>());
}