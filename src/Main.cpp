#include <thread>

#include "Menu/Menu.hpp"

Menu* menu = new Menu;

void Main()
{

}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
    {
        std::thread main(Main);
        main.detach();
    }

    return TRUE;
}