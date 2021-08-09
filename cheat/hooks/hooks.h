#pragma once
#include "hook/hook.h"
#include "../cheat.h"
#include <Windows.h>
class hooks
{
public:
	hooks();
	void hook();
	void unhook();

	cheat* icheat;
};