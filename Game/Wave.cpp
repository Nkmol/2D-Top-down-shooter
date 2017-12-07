#include "Wave.h"


static void from_json(const nlohmann::json& j, FlockVars& value)
{
	value.type = j.at("type").get<int>();
	value.amount = j.at("amount").get<int>();
	value.minPos = j.at("minPos").get<int>();
	value.maxPos = j.at("maxPos").get<int>();
}

void from_json(const nlohmann::json& j, Wave& value)
{
	value.SetId(j.at("id").get<int>());
	value.SetTime(j.at("time").get<float>());
	value.SetMultiplier(j.at("multiplier").get<float>());
	value.SetFlocksVars(j.at("flocks").get<std::vector<FlockVars>>());
}