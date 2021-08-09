#include "cheat.h"
#include <iostream>

#include "drawing/drawing.h"
#include "hooks/hooks.h"
#include "menu/menu.h"
#include "settings/settings.h"
#include "../cheat/modules/radio/radio.h"

cheat::cheat(HMODULE handle)
{
    this->thread = handle;
    this->idrawing = new drawing();
    this->ihooks = new hooks();
    this->ihooks->icheat = this;
    this->iradio = new radio();
    this->isettings = new settings();
    this->imenu = new menu(this);
}

void cheat::run()
{
    AllocConsole();
    SetConsoleCtrlHandler(NULL, true);
    FILE* f;
    freopen_s(&f, "CONOUT$", "w", stdout);
    this->iradio->np = this->iradio->getInfo()["main"]["np"].get<std::string>();
    this->ihooks->hook();
    while (!GetAsyncKeyState(VK_END))
    {
        this->iradio->getInfo();
        //std::cout << "ITS IN THE WAY THAT YOU USE IT~ ~ ~ ~ " << std::endl;
        Sleep(10);
    }
    this->ihooks->unhook();
    fclose(f);
    FreeConsole();
    FreeLibraryAndExitThread(this->thread, 0);
}