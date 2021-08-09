#pragma once
#include <map>
#include <string>

#define SETTING_BOOL 0
#define SETTING_INT 1
struct settingValue
{
	int type;
	int value;
	int min;
	int max;
};

class settings
{
public:
	settings();
	std::map<std::string, settingValue> menu;
	std::map<std::string, settingValue> other;
};