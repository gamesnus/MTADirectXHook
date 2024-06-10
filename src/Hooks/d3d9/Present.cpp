#include "MinHook.h"
#include "Menu/Menu.hpp"

#include "Present.hpp"

using tPresent = HRESULT(__stdcall*)(IDirect3DDevice9*, const RECT*, const RECT*, HWND, const RGNDATA*);
tPresent oPresent;

HRESULT __stdcall hkPresent(IDirect3DDevice9* self, const RECT* sourceRect, const RECT* destRect, HWND destWindowOverride, const RGNDATA* dirtyRegion)
{
    menu->Init(self);
    menu->Draw();
    return oPresent(self, sourceRect, destRect, destWindowOverride, dirtyRegion);
}

void Present::InstallHook()
{
    MH_STATUS status;

    if (const auto& module = reinterpret_cast<DWORD>(GetModuleHandleA("d3d9.dll")))
    {
        if (const auto& target = reinterpret_cast<LPVOID>(module + 0xE34A0))
        {
            status = MH_CreateHook(target, &hkPresent, reinterpret_cast<LPVOID*>(&oPresent));
            if (status != MH_OK)
            {
                // err handle
            }

            status = MH_EnableHook(target);
            if (status != MH_OK)
            {
                // err handle
            }
        }
    }
}

void Present::RemoveHook()
{
    MH_STATUS status;

    if (const auto& module = reinterpret_cast<DWORD>(GetModuleHandleA("d3d9.dll")))
    {
        if (const auto& target = reinterpret_cast<LPVOID>(module + 0xE34A0))
        {
            status = MH_DisableHook(target);
            if (status != MH_OK)
            {
                // err handle
            }

            status = MH_RemoveHook(target);
            if (status != MH_OK)
            {
                // err handle
            }
        }
    }
}