#include "drawing.h"
#include <vector>
#include "../../lib/csgo/offsets.h"

drawing::drawing()
{
	this->device = 0; // set in hooked endscene
	this->font = 0;
	this->fontLarge = 0;
}

void drawing::drawFilledRect(int x, int y, int w, int h, D3DCOLOR color)
{
    D3DRECT rect = { x, y, x + w, y + h };
    this->device->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0);
}

void drawing::drawPixel(int x, int y, D3DCOLOR color)
{
    drawing::drawFilledRect(x, y, 1, 1, color);
}

void drawing::drawFilledRect2(int x, int y, int w, int h, D3DCOLOR color)
{
    D3DRECT rect = { x, y, w, h };
    this->device->Clear(1, &rect, D3DCLEAR_TARGET, color, 0, 0); // i think this is supposed to be ColorFill but i don't want to fufill the args
}

void drawing::drawLine(float x1, float y1, float x2, float y2, float width, bool antialias, D3DCOLOR color)
{
    ID3DXLine* m_Line;

    D3DXCreateLine(this->device, &m_Line);
    D3DXVECTOR2 line[] = { D3DXVECTOR2(x1, y1), D3DXVECTOR2(x2, y2) };
    m_Line->SetWidth(width);
    if (antialias) m_Line->SetAntialias(1);
    m_Line->Begin();
    m_Line->Draw(line, 2, color);
    m_Line->End();
    m_Line->Release();
}

void drawing::drawText(LPD3DXFONT font, unsigned int x, unsigned int y, D3DCOLOR fontColor, LPCSTR Message)
{
    RECT rct;
    rct.left = x;
    rct.right = 1920; // note todo dolater marker important info: make this dynamic im catchign autism
    rct.top = y;
    rct.bottom = rct.top + 200;
    font->DrawTextA(NULL, Message, -1, &rct, 0, fontColor);
}

int drawing::getTextWidth(const char* text, LPD3DXFONT font)
{
    RECT rect = { 0,0,0,0 };
    if (font)
    {
        font->DrawText(NULL, text, strlen(text), &rect, DT_CALCRECT,
            D3DCOLOR_XRGB(0, 0, 0));
    }
    return (rect.right - rect.left);
}

color drawing::HSV2RGB(float H, float S, float V)
{
    while (H > 360 || H < 0)
    {
        H = abs(H - 360);
    }
    float s = S / 100;
    float v = V / 100;
    float C = s * v;
    float X = C * (1 - abs(fmod(H / 60.0, 2) - 1));
    float m = v - C;
    float r, g, b;
    if (H >= 0 && H < 60)
    {
        r = C, g = X, b = 0;
    }
    else if (H >= 60 && H < 120)
    {
        r = X, g = C, b = 0;
    }
    else if (H >= 120 && H < 180)
    {
        r = 0, g = C, b = X;
    }
    else if (H >= 180 && H < 240)
    {
        r = 0, g = X, b = C;
    }
    else if (H >= 240 && H < 300)
    {
        r = X, g = 0, b = C;
    }
    else
    {
        r = C, g = 0, b = X;
    }
    color ret;
    ret.r = (r + m) * 255;
    ret.g = (g + m) * 255;
    ret.b = (b + m) * 255;
    return ret;
}