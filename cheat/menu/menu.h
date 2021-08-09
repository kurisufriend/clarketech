#pragma once
#include <string>
#include <vector>
#include "../drawing/drawing.h"
#include "../settings/settings.h"
#include "../modules/radio/radio.h"
#include "../cheat.h"
#include "../../lib/csgo/vector2.h"
class menu
{
public:
	menu(cheat* cheat_);

	drawing* idrawing;
	settings* isettings;
	radio* iradio;
	bool open;
	vector2 mouse;
	vector2 base { 0, 4 }; // gotta stop this "start at y=4" business. it's not proper.
	int currentTab;
	color iwtcird;

	bool isMouseInRect(int x1, int y1, int x2, int y2);
	void drawButton(std::string label, int x1, int& y1, void(*callback)(), D3DCOLOR color);
	void drawMutex(std::string label, int x1, int& y1, int& tracker, std::vector<std::string> options, D3DCOLOR color);
	void drawCycle(std::string label, int x1, int& y1, int& tracker, std::vector<std::string> options, D3DCOLOR color);
	void drawToggle(std::string label, int x1, int& y1, int& tracker, D3DCOLOR color);
	void drawTab(std::string label, int& x1, int y1, int& tracker, int tab);
	void drawSlider(std::string label, int x1, int& y1, int& tracker, int min, int max, D3DCOLOR color);
	void drawSeparator(int& y);
	void render();
};