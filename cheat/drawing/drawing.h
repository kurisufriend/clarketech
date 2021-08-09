#pragma once
#include "../../lib/dxsdk/Include/d3d9.h"
#include "../../lib/dxsdk/Include/d3dx9.h"
#pragma comment(lib, "lib/dxsdk/Lib/x86/d3d9.lib")
#pragma comment(lib, "lib/dxsdk/Lib/x86/d3dx9.lib")
struct color { float r, g, b;  };
class drawing
{
public:
	drawing();
	LPDIRECT3DDEVICE9 device;
	LPD3DXFONT font;
	LPD3DXFONT fontLarge;

	void drawFilledRect(int x, int y, int w, int h, D3DCOLOR color);
	void drawPixel(int x, int y, D3DCOLOR color);
	void drawFilledRect2(int x, int y, int w, int h, D3DCOLOR color);
	void drawLine(float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color);
	void drawText(LPD3DXFONT font, unsigned int x, unsigned int y, D3DCOLOR fontColor, LPCSTR Message);
	int getTextWidth(const char* szText, LPD3DXFONT pFont);
	color HSV2RGB(float H, float S, float V);
};