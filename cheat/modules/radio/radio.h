#pragma once
#include "../../../lib/json/json.h"
class radio
{
public:
	radio();
	std::string resCache;

	std::string np;
	std::string dj;
	int endtime{ 0 };

	nlohmann::json getInfo();
};