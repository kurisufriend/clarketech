#include "menu.h"
#include <iostream>
#include <numeric>
#include <cmath>
#include <Windows.h>
#include <time.h>

#include "../modules/radio/radio.h"

#define PADDINGVALUE 5

menu::menu(cheat* cheat_)
{
	this->mouse.x = 0;
	this->mouse.y = 0;
	this->open = false;
	this->idrawing = cheat_->idrawing;
	this->isettings = cheat_->isettings;
	this->iradio = cheat_->iradio;
}

bool menu::isMouseInRect(int x1, int y1, int x2, int y2) // ill just hope i never make any non-rectangle controls
{
	return (this->mouse.x > x1 && this->mouse.y > y1 && this->mouse.x < x2 && this->mouse.y < y2);
}

void menu::drawButton(std::string label, int x1, int& y1, void(*callback)(), D3DCOLOR color)
{
	y1 += 25 + PADDINGVALUE;
	int x2 = x1 + this->idrawing->getTextWidth(label.c_str(), this->idrawing->font);
	int y2 = y1 + 17;
	bool isHovered = isMouseInRect(x1, y1, x2, y2);
	bool isPressed = (isHovered && (GetAsyncKeyState(VK_LBUTTON) & 0x8000));
	if (isHovered)
		color = D3DCOLOR_ARGB(255, 120, 120, 120);
	if (isPressed)
	{
		color = D3DCOLOR_ARGB(255, 210, 210, 0);
		callback();
	}
	this->idrawing->drawFilledRect2(x1, y1, x2, y2, color);
	this->idrawing->drawText(this->idrawing->font, x1, y1, D3DCOLOR_ARGB(255, 255, 255, 255), label.c_str());
}

void menu::drawCycle(std::string label, int x1, int& y1, int& tracker, std::vector<std::string> options, D3DCOLOR color)
{/*
	int maxSize = -1;
	std::string maxString;
	for (int i = 0; i < options.size(); i++)
	{
		std::string curOption = options.at(i);
		//int curSize = this->idrawing->getTextWidth(curOption.c_str(), this->idrawing->font);
		int curSize = curOption.length();
		if (curSize > maxSize)
		{
			maxSize = curSize;
			maxString = curOption;
		}
	}
	y1 += 25 + PADDINGVALUE;
	this->idrawing->drawText(this->idrawing->font, x1, y1, D3DCOLOR_ARGB(255, 255, 255, 255), label.c_str());
	y1 += 17;
	std::string option = options.at(i);
	int x2 = x1 + this->idrawing->getTextWidth(maxString.c_str(), this->idrawing->font);
	int y2 = y1 + 17;
	bool isHovered = isMouseInRect(x1, y1, x2, y2);
	bool isPressed = (isHovered && (GetAsyncKeyState(VK_LBUTTON) & 0x8000));
	if (isHovered)
		color = D3DCOLOR_ARGB(255, 120, 120, 120);
	D3DCOLOR textColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	if (isPressed)
	{
		color = D3DCOLOR_ARGB(255, 210, 210, 0);
		textColor = D3DCOLOR_ARGB(255, 0, 0, 0);
		tracker++;
	}
	this->idrawing->drawFilledRect2(x1, y1, x2, y2, color);
	this->idrawing->drawText(this->idrawing->font, x1, y1, textColor, option.c_str());*/
}

void menu::drawMutex(std::string label, int x1, int& y1, int& tracker, std::vector<std::string> options, D3DCOLOR color)
{
	int maxSize = -1;
	std::string maxString;
	for (int i = 0; i < options.size(); i++)
	{
		std::string curOption = options.at(i);
		//int curSize = this->idrawing->getTextWidth(curOption.c_str(), this->idrawing->font);
		int curSize = curOption.length();
		if (curSize > maxSize)
		{
			maxSize = curSize;
			maxString = curOption;
		}
	}
	D3DCOLOR oldColor = color;
	y1 += 25 + PADDINGVALUE;
	this->idrawing->drawText(this->idrawing->font, x1, y1, D3DCOLOR_ARGB(255, 255, 255, 255), label.c_str());
	for (int i = 0; i < options.size(); i++)
	{
		color = oldColor;
		y1 += 17;
		std::string option = options.at(i);
		int x2 = x1 + this->idrawing->getTextWidth(maxString.c_str(), this->idrawing->font);
		int y2 = y1 + 17;
		bool isHovered = isMouseInRect(x1, y1, x2, y2);
		bool isPressed = (isHovered && (GetAsyncKeyState(VK_LBUTTON) & 0x8000));
		if (isHovered)
			color = D3DCOLOR_ARGB(255, 120, 120, 120);
		D3DCOLOR textColor = D3DCOLOR_ARGB(255, 255, 255, 255);
		if (isPressed || i == tracker)
		{
			color = D3DCOLOR_ARGB(255, 210, 210, 0);
			textColor = D3DCOLOR_ARGB(255, 0, 0, 0);
			tracker = i;
		}
		this->idrawing->drawFilledRect2(x1, y1, x2, y2, color);
		this->idrawing->drawText(this->idrawing->font, x1, y1, textColor, option.c_str());
	}
}

void menu::drawToggle(std::string label, int x1, int& y1, int& tracker, D3DCOLOR color)
{
	y1 += 25 + PADDINGVALUE;
	int x2 = x1 + 17;
	int y2 = y1 + 17;
	bool isHovered = isMouseInRect(x1, y1, x2, y2);
	bool isPressed = (isHovered && (GetAsyncKeyState(VK_LBUTTON) & 0x1));
	if (isHovered)
		color = D3DCOLOR_ARGB(255, 120, 120, 120);
	D3DCOLOR pressColor = color;
	if (isPressed)
	{
		if (tracker)
			tracker = 0;
		else if (!tracker)
			tracker = 1;
		//tracker = !tracker;
	}
	pressColor = tracker ? D3DCOLOR_ARGB(255, 210, 210, 0) : color;
	this->idrawing->drawFilledRect2(x1, y1, x2, y2, color);
	this->idrawing->drawFilledRect2(x1 + 1, y1 + 1, x2 - 1, y2 - 1, pressColor);
	this->idrawing->drawText(this->idrawing->font, x2, y1, D3DCOLOR_ARGB(255, 255, 255, 255), label.c_str());
	//std::cout << tracker << std::endl;
}

void menu::drawTab(std::string label, int& x1, int y1, int& tracker, int tab)
{
	int x2 = x1 + this->idrawing->getTextWidth(label.c_str(), this->idrawing->font);
	int y2 = y1 + 17 + 2;
	bool isHovered = isMouseInRect(x1, y1, x2, y2);
	bool isPressed = (isHovered && (GetAsyncKeyState(VK_LBUTTON) & 0x8000));
	D3DCOLOR color = isHovered ? D3DCOLOR_ARGB(255, 210, 210, 0) : D3DCOLOR_ARGB(255, 120, 120, 120);
	if (tracker == tab)
		color = D3DCOLOR_ARGB(255, 210, 210, 0);
	if (isPressed)
	{
		tracker = tab;
	}
	this->idrawing->drawText(this->idrawing->font, x1, y1, D3DCOLOR_ARGB(255, 255, 255, 255), label.c_str());
	this->idrawing->drawLine(x1, y2, x2, y2, 1, false, color);
	x1 += (PADDINGVALUE * 2) + this->idrawing->getTextWidth(label.c_str(), this->idrawing->font);
}

void menu::drawSlider(std::string label, int x1, int& y1, int& tracker, int min, int max, D3DCOLOR color)
{
	y1 += 25 + PADDINGVALUE;
	int x2 = x1 + 200;
	int y2 = y1 + 17;
	bool isHovered = isMouseInRect(x1, y1, x2, y2);
	bool isPressed = (isHovered && (GetAsyncKeyState(VK_LBUTTON) & 0x8000));
	if (isHovered)
		color = D3DCOLOR_ARGB(255, 120, 120, 120);
	int sliderX = std::lrint((float)x1 + ((float)tracker * (200.f / (float)max))); // fuck doubles
	if (isPressed)
	{
		sliderX = this->mouse.x;
		tracker = std::lrint(((this->mouse.x - x1) / 200.f) * (float)max);
	}
	D3DCOLOR textColor;
	if (sliderX > (x1 + this->idrawing->getTextWidth(label.c_str(), this->idrawing->font)))
		textColor = D3DCOLOR_ARGB(255, 0, 0, 0);
	else
		textColor = D3DCOLOR_ARGB(255, 255, 255, 255);
	this->idrawing->drawFilledRect2(x1, y1, x2, y2, color);
	this->idrawing->drawFilledRect2(x1, y1, sliderX, y2, D3DCOLOR_ARGB(255, 210, 210, 0));
	this->idrawing->drawText(this->idrawing->font, x1, y1, textColor, label.c_str());
	this->idrawing->drawText(this->idrawing->font, x2 + PADDINGVALUE, y1, D3DCOLOR_ARGB(255, 255, 255, 255), std::to_string(tracker).c_str());
}

void menu::drawSeparator(int& y) // im lazy
{
	y += 25 + PADDINGVALUE;
}

void menu::render()
{
	if (GetAsyncKeyState(VK_INSERT) & 0xFFF)
		this->open = !this->open;
	if (!this->open)
		return;
	float width = 800, height = 500;
	static float counter = 1;
	if (this->isettings->menu["trannysenseRainbow"].value)
	{
		counter += .2f;
		//std::cout << counter << std::endl;
		for (int i = 0; i < width; i++)
		{
			this->iwtcird = this->idrawing->HSV2RGB(counter + (i/2.5), 100, 80);
			this->idrawing->drawFilledRect2(this->base.x + i, this->base.y - 4, this->base.x + i + 1, this->base.y + height, D3DCOLOR_ARGB(255, (int)this->iwtcird.r, (int)this->iwtcird.g, (int)this->iwtcird.b));
		}
	}

	//this->iwtcird = this->idrawing->HSV2RGB(counter, 100, 80);
	//this->idrawing->drawFilledRect2(this->base.x, this->base.y - 4, this->base.x + width, this->base.y + height, D3DCOLOR_ARGB(255, (int)this->iwtcird.r, (int)this->iwtcird.g, (int)this->iwtcird.b));
	this->idrawing->drawFilledRect2(this->base.x, this->base.y, this->base.x + width, this->base.y + height, D3DCOLOR_ARGB(255, 20, 20, 20));
	this->idrawing->drawFilledRect2(this->base.x, this->base.y, this->base.x + width, this->base.y + height - 20, D3DCOLOR_ARGB(255, 13, 11, 15));
	this->idrawing->drawText(this->idrawing->fontLarge, (this->base.x + (width / 2)) - ((this->idrawing->getTextWidth("DIEGESIS", this->idrawing->fontLarge) / 2)), this->base.y, D3DCOLOR_ARGB(255, 240, 240, 240), "DIEGESIS");
	this->idrawing->drawText(this->idrawing->font, this->base.x, this->base.y + height - 20, D3DCOLOR_ARGB(255, 240, 240, 240), "(c) cynic.moe 2021 orgnial chit do not steal");
	int x = this->base.x;
	std::vector<std::string> tabs {"menu", "r/a/dio"};
	for (int i = 0; i < tabs.size(); i++)
	{
		this->drawTab(tabs.at(i), x, this->base.y + 25, this->currentTab, i);
	}
	int y = this->base.y + 50;
	if (this->currentTab == 0)
	{
		for (std::pair<std::string, settingValue> shittyHackSolution : this->isettings->menu)//im too fucking lazy to figure out how to get proper refs to the svlas
		{
			if (shittyHackSolution.second.type == SETTING_BOOL)
			{
				this->drawToggle(shittyHackSolution.first, this->base.x, y, this->isettings->menu[shittyHackSolution.first].value, D3DCOLOR_ARGB(255, 25, 25, 25));
			}
			else if (shittyHackSolution.second.type == SETTING_INT)
			{
				this->drawSlider(shittyHackSolution.first, this->base.x, y, this->isettings->menu[shittyHackSolution.first].value, shittyHackSolution.second.min, shittyHackSolution.second.max, D3DCOLOR_ARGB(255, 25, 25, 25));
			}
		}
		//this->drawToggle("trannysense rainbow", this->base.x, y, this->isettings->menu["trannysenseRainbow"].value, D3DCOLOR_ARGB(255, 25, 25, 25));
	}
	else if (this->currentTab == 1)
	{
		//std::cout << this->iradio->np << std::endl;
		this->idrawing->drawText(this->idrawing->font, this->base.x, this->base.y + 75, D3DCOLOR_ARGB(255, 240, 240, 240), this->iradio->np.c_str());
		this->idrawing->drawText(this->idrawing->font, this->base.x, this->base.y + 100, D3DCOLOR_ARGB(255, 240, 240, 240), std::to_string(this->iradio->endtime-time(NULL)).c_str());
	}
	if (GetAsyncKeyState(VK_RBUTTON) && isMouseInRect(this->base.x, this->base.y, this->base.x + width, this->base.y + height))
	{
		this->base.x = this->mouse.x - (width / 2);
		this->base.y = this->mouse.y - (height / 2);
	}
}