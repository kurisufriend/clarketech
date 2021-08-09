//object-oriented canceraids inc.
/*

    ,o888888o.    8 8888                  .8.          8 888888888o.   8 8888     ,88' 8 8888888888 8888888 8888888888 8 8888888888       ,o888888o.    8 8888        8
   8888     `88.  8 8888                 .888.         8 8888    `88.  8 8888    ,88'  8 8888             8 8888       8 8888            8888     `88.  8 8888        8
,8 8888       `8. 8 8888                :88888.        8 8888     `88  8 8888   ,88'   8 8888             8 8888       8 8888         ,8 8888       `8. 8 8888        8
88 8888           8 8888               . `88888.       8 8888     ,88  8 8888  ,88'    8 8888             8 8888       8 8888         88 8888           8 8888        8
88 8888           8 8888              .8. `88888.      8 8888.   ,88'  8 8888 ,88'     8 888888888888     8 8888       8 888888888888 88 8888           8 8888        8
88 8888           8 8888             .8`8. `88888.     8 888888888P'   8 8888 88'      8 8888             8 8888       8 8888         88 8888           8 8888        8
88 8888           8 8888            .8' `8. `88888.    8 8888`8b       8 888888<       8 8888             8 8888       8 8888         88 8888           8 8888888888888
`8 8888       .8' 8 8888           .8'   `8. `88888.   8 8888 `8b.     8 8888 `Y8.     8 8888             8 8888       8 8888         `8 8888       .8' 8 8888        8
   8888     ,88'  8 8888          .888888888. `88888.  8 8888   `8b.   8 8888   `Y8.   8 8888             8 8888       8 8888            8888     ,88'  8 8888        8
    `8888888P'    8 888888888888 .8'       `8. `88888. 8 8888     `88. 8 8888     `Y8. 8 888888888888     8 8888       8 888888888888     `8888888P'    8 8888        8

presented by cynic
i've no clue how oop is actually supposed to work, so this will have to do
s/o vc, zoat, all of the cool kids on efnet, /prog/, etc.

TOADD:

TOFIX:

*/
#include <Windows.h>

#include "cheat/cheat.h"

void dattebayo(HMODULE handle)
{
    cheat c = cheat(handle);
    c.run();
}

BOOL APIENTRY DllMain(HMODULE handle, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
        CloseHandle(CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)dattebayo, handle, NULL, nullptr));
    return TRUE;
}