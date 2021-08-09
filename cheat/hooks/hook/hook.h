#pragma once
struct hook
{
	void* target;
	void* detour;
	void** original;
};