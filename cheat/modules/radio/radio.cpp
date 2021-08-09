#include "radio.h"
#include "../../../lib/httplib/httplib.h"
#include <iostream>
#include <time.h>
radio::radio()
{
	this->resCache = "";
	this->np = "";
}
nlohmann::json radio::getInfo()
{
	if (this->endtime == 0 || this->endtime <= time(NULL))
	{
		std::cout << "new song~" << std::endl;
		httplib::Client cli("http://r-a-d.io");

		auto res = cli.Get("/api");
		this->resCache = res->body;
		nlohmann::json jsonRes = nlohmann::json::parse(res->body);
		this->np = jsonRes["main"]["np"].get<std::string>();
		this->dj = jsonRes["main"]["djname"].get<std::string>();
		this->endtime = jsonRes["main"]["end_time"].get<int>();
		return jsonRes;
	}
	else
	{
		return nlohmann::json::parse(this->resCache);
	}
}