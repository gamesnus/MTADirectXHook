#include "MinHook.h"
#include "Menu/Menu.hpp"

#include "SetCursorPos.hpp"

using tSetCursorPos = BOOL(WINAPI*)(int, int);
tSetCursorPos oSetCursorPos;

BOOL WINAPI hkSetCursorPos(int X, int Y)
{
    if (menu->GetState())
    {
        return FALSE;
    }

    return oSetCursorPos(X, Y);
}

void SetCursorPos::InstallHook()
{
    MH_STATUS status;

    status = MH_CreateHook(&::SetCursorPos, &hkSetCursorPos, reinterpret_cast<LPVOID*>(&oSetCursorPos));
    if (status != MH_OK)
    {
        // err handle
    }

    status = MH_EnableHook(&::SetCursorPos);
    if (status != MH_OK)
    {
        // err handle
    }
}

void SetCursorPos::RemoveHook()
{
    MH_STATUS status;

    status = MH_DisableHook(&::SetCursorPos);
    if (status != MH_OK)
    {
        // err handle
    }

    status = MH_RemoveHook(&::SetCursorPos);
    if (status != MH_OK)
    {
        // err handle
    }
}