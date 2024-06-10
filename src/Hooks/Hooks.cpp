#include "MinHook.h"

#include "user32/SetCursorPos.hpp"

#include "d3d9/Present.hpp"
#include "d3d9/Reset.hpp"

#include "Hooks.hpp"

void Hooks::InstallHooks()
{
    MH_STATUS status;

    status = MH_Initialize();
    if (status != MH_OK)
    {
        // err handle
        return;
    }

    SetCursorPos::InstallHook();

    while (!GetModuleHandleA("cgui.dll"))
    {
    }

    Present::InstallHook();
    Reset::InstallHook();
}

void Hooks::RemoveHooks()
{
    MH_STATUS status;

    SetCursorPos::RemoveHook();
    Present::RemoveHook();
    Reset::RemoveHook();

    status = MH_Uninitialize();
    if (status != MH_OK)
    {
        // err handle
    }
}