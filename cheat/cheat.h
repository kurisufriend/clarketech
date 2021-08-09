#pragma once
#include <Windows.h>

class hooks;
class drawing;
class menu;
class settings;
class radio;

class cheat
{
private:
	HMODULE thread;
public:
	cheat(HMODULE handle);
	void run();

	hooks* ihooks;
	drawing* idrawing;
	menu* imenu;
	settings* isettings;
	radio* iradio;
};