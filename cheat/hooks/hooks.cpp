#include "hooks.h"

#include "../../lib/csgo/offsets.h"
#include "../../lib/minhook/MinHook.h"
#include "../drawing/drawing.h"
#include "../menu/menu.h"

typedef HRESULT(__stdcall* tEndScene)(LPDIRECT3DDEVICE9 device);
tEndScene oEndScene = 0;
typedef LRESULT(__stdcall* tWndProc)(HWND window, UINT msg, WPARAM wparm, LPARAM lparm);
tWndProc oWndProc = 0;

cheat* cheat_ = 0;
drawing* drawing_ = 0;
menu* menu_ = 0;

void __stdcall hkEndScene(LPDIRECT3DDEVICE9 device_)
{
	if (drawing_->device != device_)
		drawing_->device = device_;
	if (!drawing_->font)
		D3DXCreateFont(drawing_->device, 20, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Courier New", &drawing_->font);
	if (!drawing_->fontLarge)
		D3DXCreateFont(drawing_->device, 30, 0, FW_DONTCARE, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH, "Courier New", &drawing_->fontLarge);
	//drawing_->drawFilledRect2(10, 10, 100, 100, D3DCOLOR_ARGB(255, 255, 255, 255));
	//drawing_->drawText(drawing_->font, 0, 0, D3DCOLOR_ARGB(255, 240, 240, 240), "(c) cynic.moe 2021 orgnial chit do not steal");
	menu_->render();
	oEndScene(drawing_->device);
}

LRESULT __stdcall hkWndProc(HWND window, UINT msg, WPARAM wparm, LPARAM lparm)
{
	if (msg == WM_MOUSEMOVE)
	{
		menu_->mouse.x = LOWORD(lparm);
		menu_->mouse.y = HIWORD(lparm);
	}
	return CallWindowProcA(oWndProc, window, msg, wparm, lparm);
}

hooks::hooks() { }

void hooks::hook()
{
	cheat_ = this->icheat;
	drawing_ = cheat_->idrawing;
	menu_ = cheat_->imenu;

	IDirect3DDevice9* d3d9Device = *reinterpret_cast<IDirect3DDevice9**>(((DWORD)GetModuleHandle("shaderapidx9.dll") + hazedumper::signatures::dwppDirect3DDevice9));
	void** vTable = *reinterpret_cast<void***>(d3d9Device);
	void* EndScene = vTable[42];

	oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongA(FindWindowA("Valve001", nullptr), GWL_WNDPROC, reinterpret_cast<LONG>(hkWndProc)));

	if (MH_Initialize() != MH_OK)
		return;
	if (MH_CreateHook(EndScene, &hkEndScene, reinterpret_cast<void**>(&oEndScene)) != MH_OK)
		return;
	if (MH_EnableHook(MH_ALL_HOOKS) != MH_OK)
		return;
}

void hooks::unhook()
{
	SetWindowLongA(FindWindowA("Valve001", 0), GWL_WNDPROC, reinterpret_cast<LONG>(oWndProc));
	MH_Uninitialize();
	MH_DisableHook(MH_ALL_HOOKS);
}
